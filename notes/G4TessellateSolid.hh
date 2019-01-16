00001 //
00002 // ********************************************************************
00003 // * License and Disclaimer                                           *
00004 // *                                                                  *
00005 // * The  Geant4 software  is  copyright of the Copyright Holders  of *
00006 // * the Geant4 Collaboration.  It is provided  under  the terms  and *
00007 // * conditions of the Geant4 Software License,  included in the file *
00008 // * LICENSE and available at  http://cern.ch/geant4/license .  These *
00009 // * include a list of copyright holders.                             *
00010 // *                                                                  *
00011 // * Neither the authors of this software system, nor their employing *
00012 // * institutes,nor the agencies providing financial support for this *
00013 // * work  make  any representation or  warranty, express or implied, *
00014 // * regarding  this  software system or assume any liability for its *
00015 // * use.  Please see the license in the file  LICENSE  and URL above *
00016 // * for the full disclaimer and the limitation of liability.         *
00017 // *                                                                  *
00018 // * This  code  implementation is the result of  the  scientific and *
00019 // * technical work of the GEANT4 collaboration and of QinetiQ Ltd,   *
00020 // * subject to DEFCON 705 IPR conditions.                            *
00021 // * By using,  copying,  modifying or  distributing the software (or *
00022 // * any work based  on the software)  you  agree  to acknowledge its *
00023 // * use  in  resulting  scientific  publications,  and indicate your *
00024 // * acceptance of all terms of the Geant4 Software license.          *
00025 // ********************************************************************
00026 //
00027 // $Id: G4TessellatedSolid.hh 67011 2013-01-29 16:17:41Z gcosmo $
00028 //
00029 // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
00030 //
00031 // Class G4TessellatedSolid
00032 //
00033 // Class description:
00034 //
00035 //    G4TessellatedSolid is a special Geant4 solid defined by a number of 
00036 //    facets (UVFacet). It is important that the supplied facets shall form a
00037 //    fully enclose space which is the solid. 
00038 //    At the moment only two types of facet can be used for the construction of 
00039 //    a G4TessellatedSolid, i.e. the G4TriangularFacet and G4QuadrangularFacet.
00040 //
00041 //    How to contruct a G4TessellatedSolid:
00042 //  
00043 //    First declare a tessellated solid:
00044 //
00045 //      G4TessellatedSolid* solidTarget = new G4TessellatedSolid("Solid_name");
00046 //
00047 //    Define the facets which form the solid
00048 // 
00049 //      G4double targetSiz = 10*cm ;
00050 //      G4TriangularFacet *facet1 = new
00051 //      G4TriangularFacet (G4ThreeVector(-targetSize,-targetSize,        0.0),
00052 //                         G4ThreeVector(+targetSize,-targetSize,        0.0),
00053 //                         G4ThreeVector(        0.0,        0.0,+targetSize),
00054 //                         ABSOLUTE);
00055 //      G4TriangularFacet *facet2 = new
00056 //      G4TriangularFacet (G4ThreeVector(+targetSize,-targetSize,        0.0),
00057 //                         G4ThreeVector(+targetSize,+targetSize,        0.0),
00058 //                         G4ThreeVector(        0.0,        0.0,+targetSize),
00059 //                         ABSOLUTE);
00060 //      G4TriangularFacet *facet3 = new
00061 //      G4TriangularFacet (G4ThreeVector(+targetSize,+targetSize,        0.0),
00062 //                         G4ThreeVector(-targetSize,+targetSize,        0.0),
00063 //                         G4ThreeVector(        0.0,        0.0,+targetSize),
00064 //                         ABSOLUTE);
00065 //      G4TriangularFacet *facet4 = new
00066 //      G4TriangularFacet (G4ThreeVector(-targetSize,+targetSize,        0.0),
00067 //                         G4ThreeVector(-targetSize,-targetSize,        0.0),
00068 //                         G4ThreeVector(        0.0,        0.0,+targetSize),
00069 //                         ABSOLUTE);
00070 //      G4QuadrangularFacet *facet5 = new
00071 //      G4QuadrangularFacet (G4ThreeVector(-targetSize,-targetSize,      0.0),
00072 //                           G4ThreeVector(-targetSize,+targetSize,      0.0),
00073 //                           G4ThreeVector(+targetSize,+targetSize,      0.0),
00074 //                           G4ThreeVector(+targetSize,-targetSize,      0.0),
00075 //                           ABSOLUTE);
00076 //
00077 //    Then add the facets to the solid:    
00078 //
00079 //      solidTarget->AddFacet((UVFacet*) facet1);
00080 //      solidTarget->AddFacet((UVFacet*) facet2);
00081 //      solidTarget->AddFacet((UVFacet*) facet3);
00082 //      solidTarget->AddFacet((UVFacet*) facet4);
00083 //      solidTarget->AddFacet((UVFacet*) facet5);
00084 //
00085 //    Finally declare the solid is complete:
00086 //
00087 //      solidTarget->SetSolidClosed(true);
00088 
00089 // CHANGE HISTORY
00090 // --------------
00091 // 31 October 2004, P R Truscott, QinetiQ Ltd, UK
00092 //  - Created.
00093 // 22 November 2005, F Lei, 
00094 //  - Added GetPolyhedron().
00095 // 12 October 2012, M Gayer,
00096 //  - Reviewed optimized implementation including voxelization of surfaces.
00097 //
00099 #ifndef G4TessellatedSolid_hh
00100 #define G4TessellatedSolid_hh 1
00101 
00102 #include <iostream>
00103 #include <vector>
00104 #include <set>
00105 #include <map>
00106 
00107 #include "G4VSolid.hh"
00108 #include "G4Types.hh"
00109 #include "G4SurfaceVoxelizer.hh"
00110 
00111 struct G4VertexInfo
00112 {
00113   G4int id;
00114   G4double mag2;
00115 };
00116 
00117 class G4VFacet;
00118 
00119 class G4VertexComparator
00120 {
00121 public:
00122   G4bool operator() (const G4VertexInfo &l, const G4VertexInfo &r) const
00123   {
00124     return l.mag2 == r.mag2 ? l.id < r.id : l.mag2 < r.mag2;
00125   }
00126 };
00127 
00128 class G4TessellatedSolid : public G4VSolid
00129 {
00130   public:  // with description
00131 
00132     G4TessellatedSolid ();
00133     virtual ~G4TessellatedSolid ();
00134 
00135     G4TessellatedSolid (const G4String &name);
00136 
00137     G4TessellatedSolid(__void__&);
00138       // Fake default constructor for usage restricted to direct object
00139       // persistency for clients requiring preallocation of memory for
00140       // persistifiable objects.
00141 
00142     G4TessellatedSolid (const G4TessellatedSolid &ts);
00143     G4TessellatedSolid &operator= (const G4TessellatedSolid &right);
00144     G4TessellatedSolid &operator+= (const G4TessellatedSolid &right);
00145 
00146     G4bool AddFacet (G4VFacet *aFacet);
00147     inline G4VFacet *GetFacet (G4int i) const;
00148 
00149     G4int GetNumberOfFacets () const;
00150 
00151     virtual EInside Inside (const G4ThreeVector &p) const;
00152     virtual G4ThreeVector SurfaceNormal(const G4ThreeVector& p) const;
00153     virtual G4double DistanceToIn(const G4ThreeVector& p,
00154                                   const G4ThreeVector& v)const;
00155     virtual G4double DistanceToIn(const G4ThreeVector& p) const;
00156     virtual G4double DistanceToOut(const G4ThreeVector& p) const;
00157     virtual G4double DistanceToOut(const G4ThreeVector& p,
00158                                    const G4ThreeVector& v,
00159                                    const G4bool calcNorm,
00160                                          G4bool *validNorm,
00161                                          G4ThreeVector *norm) const;
00162 
00163     virtual G4bool Normal (const G4ThreeVector &p, G4ThreeVector &n) const;
00164     virtual G4double SafetyFromOutside(const G4ThreeVector &p,
00165                                              G4bool aAccurate=false) const;
00166     virtual G4double SafetyFromInside (const G4ThreeVector &p,
00167                                              G4bool aAccurate=false) const;
00168 
00169     virtual G4GeometryType GetEntityType () const;
00170     virtual std::ostream &StreamInfo(std::ostream &os) const;
00171 
00172     virtual G4VSolid* Clone() const;
00173 
00174     virtual G4ThreeVector GetPointOnSurface() const;
00175     virtual G4double GetSurfaceArea();
00176     virtual G4double GetCubicVolume ();
00177 
00178     void SetSolidClosed (const G4bool t);
00179     G4bool GetSolidClosed () const;
00180 
00181     inline void SetMaxVoxels(G4int max);
00182 
00183     inline G4SurfaceVoxelizer &GetVoxels();
00184 
00185     virtual G4bool CalculateExtent(const EAxis pAxis,
00186                                    const G4VoxelLimits& pVoxelLimit,
00187                                    const G4AffineTransform& pTransform,
00188                                          G4double& pMin, G4double& pMax) const;
00189 
00190     G4double      GetMinXExtent () const;
00191     G4double      GetMaxXExtent () const;
00192     G4double      GetMinYExtent () const;
00193     G4double      GetMaxYExtent () const;
00194     G4double      GetMinZExtent () const;
00195     G4double      GetMaxZExtent () const;
00196 
00197     G4ThreeVectorList* CreateRotatedVertices(const G4AffineTransform& pT) const;
00198       // Create the List of transformed vertices in the format required
00199       // for G4VSolid:: ClipCrossSection and ClipBetweenSections.
00200 
00201     virtual G4Polyhedron* CreatePolyhedron () const;
00202     virtual G4Polyhedron* GetPolyhedron    () const;
00203     virtual G4NURBS*      CreateNURBS      () const;
00204     virtual void DescribeYourselfTo (G4VGraphicsScene& scene) const;
00205     virtual G4VisExtent   GetExtent () const;
00206 
00207     G4int AllocatedMemoryWithoutVoxels();
00208     G4int AllocatedMemory();
00209     void DisplayAllocatedMemory();
00210 
00211   private: // without description
00212 
00213     void Initialize();
00214 
00215     G4double DistanceToOutNoVoxels(const G4ThreeVector &p,
00216                                    const G4ThreeVector &v,
00217                                          G4ThreeVector &aNormalVector,
00218                                          G4bool        &aConvex,
00219                                          G4double aPstep = kInfinity) const;
00220     G4double DistanceToInCandidates(const std::vector<G4int> &candidates,
00221                                     const G4ThreeVector &aPoint,
00222                                     const G4ThreeVector &aDirection) const;
00223     void DistanceToOutCandidates(const std::vector<G4int> &candidates,
00224                                  const G4ThreeVector &aPoint,
00225                                  const G4ThreeVector &direction,
00226                                        G4double &minDist,
00227                                        G4ThreeVector &minNormal,
00228                                        G4int &minCandidate) const;
00229     G4double DistanceToInNoVoxels(const G4ThreeVector &p,
00230                                   const G4ThreeVector &v,
00231                                         G4double aPstep = kInfinity) const;
00232     void SetExtremeFacets();
00233 
00234     EInside InsideNoVoxels (const G4ThreeVector &p) const;
00235     EInside InsideVoxels(const G4ThreeVector &aPoint) const;
00236 
00237     void Voxelize();
00238 
00239     void CreateVertexList();
00240 
00241     void PrecalculateInsides();
00242 
00243     void SetRandomVectors();
00244 
00245     G4double DistanceToInCore(const G4ThreeVector &p, const G4ThreeVector &v,
00246                                     G4double aPstep = kInfinity) const;
00247     G4double DistanceToOutCore(const G4ThreeVector &p, const G4ThreeVector &v,
00248                                      G4ThreeVector &aNormalVector,
00249                                      G4bool        &aConvex,
00250                                      G4double aPstep = kInfinity) const;
00251 
00252     G4int SetAllUsingStack(const std::vector<G4int> &voxel,
00253                            const std::vector<G4int> &max,
00254                                  G4bool status, G4SurfBits &checked);
00255 
00256     void DeleteObjects ();
00257     void CopyObjects (const G4TessellatedSolid &s);
00258 
00259     static G4bool CompareSortedVoxel(const std::pair<G4int, G4double> &l,
00260                                      const std::pair<G4int, G4double> &r);
00261 
00262     G4double MinDistanceFacet(const G4ThreeVector &p, G4bool simple,
00263                                     G4VFacet * &facet) const;
00264 
00265     inline G4bool OutsideOfExtent(const G4ThreeVector &p,
00266                                         G4double tolerance=0) const;
00267 
00268   private:
00269 
00270     mutable G4Polyhedron* fpPolyhedron;
00271 
00272     std::vector<G4VFacet *>  fFacets;
00273     std::set<G4VFacet *> fExtremeFacets; // Does all other facets lie on
00274                                          // or behind this surface?
00275 
00276     G4GeometryType           fGeometryType;
00277     G4double                 fCubicVolume;
00278     G4double                 fSurfaceArea;
00279 
00280     std::vector<G4ThreeVector>  fVertexList;
00281 
00282     std::set<G4VertexInfo,G4VertexComparator> fFacetList;
00283 
00284     G4ThreeVector fMinExtent, fMaxExtent;
00285 
00286     G4bool fSolidClosed;
00287 
00288     std::vector<G4ThreeVector> fRandir;
00289 
00290     G4double kCarToleranceHalf;
00291 
00292     G4int fMaxTries;
00293 
00294     G4SurfaceVoxelizer fVoxels;  // Pointer to the voxelized solid
00295 
00296     G4SurfBits fInsides;
00297 };
00298 
00300 // Inlined Methods
00302 
00303 inline G4VFacet *G4TessellatedSolid::GetFacet (G4int i) const
00304 {
00305   return fFacets[i];
00306 }
00307 
00308 inline void G4TessellatedSolid::SetMaxVoxels(G4int max)
00309 {
00310   fVoxels.SetMaxVoxels(max);
00311 }
00312 
00313 inline G4SurfaceVoxelizer &G4TessellatedSolid::GetVoxels()
00314 {
00315   return fVoxels;
00316 }
00317 
00318 inline G4bool G4TessellatedSolid::OutsideOfExtent(const G4ThreeVector &p,
00319                                                   G4double tolerance) const
00320 {
00321   return ( p.x() < fMinExtent.x() - tolerance
00322         || p.x() > fMaxExtent.x() + tolerance
00323         || p.y() < fMinExtent.y() - tolerance
00324         || p.y() > fMaxExtent.y() + tolerance
00325         || p.z() < fMinExtent.z() - tolerance
00326         || p.z() > fMaxExtent.z() + tolerance);
00327 }
00328 
00329 #endif
