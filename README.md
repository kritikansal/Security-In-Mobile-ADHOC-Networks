To refine the security protocols for Mobile Adhoc Networks by adding support for efficient Wormholes and Blackhole attack detection and deletions

UDG Unit Disk Graph approach to detect Wormholes: GRAPH THEORY BASED

1. In UDG each node is modeled as a disk of unit radius in the plane.
2. Each node is a neighbor of all nodes located within its disk.
3. The basic idea in our detection algorithm is to look for graph substructures that do not allow a unit disk graph embedding, thus can not be present in a legal connectivity graph.
Inside a fixed region, one cannot pack too many nodes without having edges in between. 
The forbidden substructures we look for are actually those that violate this packing argument.
Packing Number:
p(S,r) - The maximum number of points inside a region S such that every pair of points is strictly more than distance r away from each other

DR(u) - Disk of radius R centered at u.
Given two disks of radius R centered at u, v with distance r away, define by lune the intersection of the two disks, L(r, R) = DR (u) ∩ DR (v). 
p( L(r, R),β ) ≤ 8/π ( R/β +1/2 )2cos-1(r/(2R + β)) − 4r/πβ2√((R + β/2)2 − r2/4) for r ≤ 2R
p(L, 1) = 2     L:Lune with R=r=1

ALGORITHM:

Find the forbidden parameter Fk based on value of k selected
Each node u determines its 2k-hop neighbor list, N2k (u), and executes the following steps for each non neighboring node v in N2k (u):
Node u determines the set of common k-hop neighbors with v from their k-hop neighbor lists. This is Ck (u, v) = Nk (u) ∩ Nk (v)
Node u determines the maximal independent set of the sub-graph on vertices Ck (u, v) by using a greedy approach
If the maximal independent set size is equal or larger than fk , node u declares the presence of a wormhole.

