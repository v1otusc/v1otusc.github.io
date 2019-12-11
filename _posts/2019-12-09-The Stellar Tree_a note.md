---
layout: post
title: The Stellar Tree_A Note
---

<left>
By_Zihan_Zhang@seu<br/>
v1otusc@yeah.net
</left>

<!-- TOC -->

- [Notions](#notions)
- [The Stellar decomposition](#the-stellar-decomposition)
  - [1.1 Definition](#11-definition)
  - [1.2 Encoding](#12-encoding)
    - [1.2.1 Indexed representation of the CP complex](#121-indexed-representation-of-the-cp-complex)
    - [1.2.2 A compressed region representation](#122-a-compressed-region-representation)
- [The Stellar Tree](#the-stellar-tree)
  - [2.1 Definition](#21-definition)
  - [2.2 Encoding](#22-encoding)
- [Generating a Stellar tree](#generating-a-stellar-tree)
  - [3.1 Reindexing and compressing the vertices](#31-reindexing-and-compressing-the-vertices)
  - [3.2 Reindexing and compressing the top CP cells](#32-reindexing-and-compressing-the-top-cp-cells)
- [Implementation](#implementation)
- [Reference](#reference)

<!-- /TOC -->

# Notions

<big>**Topological relations**</big>

A pair of cells in CP complex are *incident* if one is a face of the other and *h-adjacent* if they have the same dimension and are incident in a common h-face.

Use n to denote the dimension of ambient space, consider a CP complex Σ with maximum dimension d and a k-cell σ ∈ Σ, with 0 ≤ k ≤ d: 

- a *boundary relation* R<sub>k, p</sub>(σ), with 0 ≤ p < k, consists of the p-cells of Σ in the boundary of σ.
- a *co-boundary relation* R<sub>k, q</sub>(σ), with k < q ≤ n, consists of the q-cells of Σ in the star of σ.
- an *adjacency relation* R<sub>k, k</sub>(σ), consists of the k-cells of Σ that are adjacent to σ. we *specially* and *infomally* refer to vetices (0-cells) as *adjacent* if they are both incident in a common edge (a 1-cell).

<big>**Star/St(σ) and Link/Lk(σ)**</big>

The *star* of σ denote St(σ):

is the set of its co-faces, i.e. CP cells in Σ that have σ as a face.

The *link* of σ denote Lk(σ):

is the set of all faces of cells in St(σ) thar are not incident in σ.

# The Stellar decomposition

Canonical Polytope (CP) complexes : a restricted class of cell complexes whose cells can be fully reconstructed by their set of vertices.

Denote a CP complex as Σ, and its ordered lists of vertices and top cells as Σ<sub>V</sub> and Σ<sub>T</sub>, respectively. 

## 1.1 Definition

A decomposition **∆** of its vertices Σ<sub>V</sub> is a collection of subsets of Σ<sub>V</sub> such that every vertex *v* ∈ Σ<sub>V</sub> belongs to at least one of these subsets.

We will refer to the elements of decomposition ∆ as regions and we will denote a region as **r**.

A Stellar decomposition(denoted by **S<sub>D</sub>**) is defined by three components:

- a CP complex Σ;
- a decomposition ∆ whose regions cover the vertices of Σ;
- a map Φ from regions of ∆ to entities of Σ.

A Stellar decomposition is a triple **S<sub>D</sub>** = (Σ,∆,Φ), Since Σ is entirely characterized by its vertices and top CP cells, we define map Φ in terms of the two components : Φ<sub>VERT</sub> defines the mapping to vertices and Φ<sub>TOP</sub> defines the mapping to **top CP cells**.

For the vertices, a map from ∆ to Σ<sub>V</sub>:

<center>
∀r ∈ ∆, Φ<sub>VERT</sub>(r) = {v ∈ Σ<sub>V</sub> : v belongs to r}
</center>

we impose the following additional property:

<center>
∀v ∈ Σ<sub>V</sub>, ∃r ∈ ∆ | v ∈ Φ<sub>VERT</sub>(r)
</center>

below is an example of mapping function Φ<sub>VERT</sub>:

<center>
<img src = "https://raw.githubusercontent.com/v1otusc/PicBed/master/vert_mapping_function.png" width = 70% height = 70%>
</center>

Formally, Φ<sub>TOP</sub> is a function from the regions of ∆ to the powerset of Σ<sub>T</sub>:

<center>
∀r ∈ ∆, Φ<sub>TOP</sub>(r) = {σ ∈ Σ<sub>T</sub> | ∃v ∈ R<sub>k,0</sub>(σ) : v ∈ Φ<sub>VERT</sub>(r)}
</center>

> k is the dimension of top cells.

below is an example of mapping function Φ<sub>TOP</sub>, for two regions (blue rectangles) of the decomposition of Figure 1(b) on a triangle mesh defined over its vertices. 

<center>
<img src = "https://raw.githubusercontent.com/v1otusc/PicBed/master/topcells_mapping_function.png" width = 90% height = 90%>
</center>

**Definition: spanning number**

As we can see in the Figure 2: A top CP cell σ is only mapped to a region *r* when one (or more) of its vertices is mapped to *r* under Φ<sub>VERT</sub>. Specifically, it does not depend on spatial overlap. To characterize this representation, we define the spanning number χ<sub>σ</sub> of top cells in a Stellar decomposition as the number of regions to which a top CP cell is mapped.

The spanning number χ<sub>σ</sub> of a CP cell σ ∈ Σ<sub>T</sub> is the number of regions in ∆ that map to σ. Formally:

<center>
∀σ ∈ Σ<sub>T</sub>, χ<sub>σ</sub> = |{r ∈ ∆ | σ ∈ Φ<sub>TOP</sub>(r)}| or #{r ∈ ∆ | σ ∈ Φ<sub>TOP</sub>(r)}
</center>

**Definition: average number**

Consider the average spanning number χ as a global characteristic of the efficiency of a Stellar decomposition over a complex measuring the average number of times each top CP cell is represented.

The average spanning number χ of a Stellar decomposition **S<sub>D</sub>** is the average number of regions indexing a top CP cell σ. Formally:

<center>
χ = (∑<sub>σ ∈ Σ<sub>T</sub></sub>χ<sub>σ</sub>) / |Σ<sub>T</sub>| = (∑<sub>r ∈ ∆</sub> | Φ<sub>TOP</sub>(r) |) / |Σ<sub>T</sub>|
</center>

## 1.2 Encoding

A detailed description of a Stellar decomposition of data structures for representing a CP complex and a compressed encoding for the regions of the decomposition.

### 1.2.1 Indexed representation of the CP complex

Assume that the underlying CP complex is representedas an indexed complex, which encodes the spatial position of the vertices and the boundary relation R<sub>k,0</sub> of each top k-simplex in Σ.



### 1.2.2 A compressed region representation



# The Stellar Tree


## 2.1 Definition


## 2.2 Encoding

# Generating a Stellar tree

## 3.1 Reindexing and compressing the vertices

## 3.2 Reindexing and compressing the top CP cells

# Implementation

I did not find the author's open source code, So I wrote one in C++ to play with it.<br/>
[Have fun]().

# Reference

- Fellegara, Riccardo, Weiss, Kenneth, De Floriani, Leila. The Stellar tree: a Compact Representation for Simplicial Complexes and Beyond[J].
