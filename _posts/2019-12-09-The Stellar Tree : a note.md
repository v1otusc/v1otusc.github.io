---
layout: post
title: The Stellar Tree : A Note
---

<center>
By zzh@seu<br/>
v1otusc@yeah.et
</center>

<!-- TOC -->

- [The Stellar decomposition](#the-stellar-decomposition)
  - [1.1 Definition](#11-definition)
  - [1.2 Encoding](#12-encoding)
- [The Stellar Tree](#the-stellar-tree)
- [Implementation](#implementation)
- [Reference](#reference)

<!-- /TOC -->

**Topological relations**

- a *boundary relation* R<sub>k, p</sub>(), with 
- a *co-boundary relation* R<sub>k, p</sub>(), with
- a *adjacency relation* R<sub>k, p</sub>(), with

# The Stellar decomposition

Canonical Polytope (CP) complexes : a restricted class of cell complexes whose cells can be fully reconstructed by their set of vertices.

Denote a CP complex as Σ, and its ordered lists of vertices and top cells as Σ<sub>V</sub> and Σ<sub>T</sub>, respectively. 

## 1.1 Definition

A decomposition **∆** of its vertices Σ<sub>V</sub> is a collection of subsets of Σ<sub>V</sub> such that every vertex *v* ∈ Σ<sub>V</sub> belongs to at least one of these subsets.

We will refer to the elements of decomposition ∆ as regions and we will denote a region as ***r***.

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
<img src = "https://raw.githubusercontent.com/v1otusc/PicBed/master/vert_mapping_function.png">
</center>

Formally, Φ<sub>TOP</sub> is a function from the regions of ∆ to the powerset of Σ<sub>T</sub>:

<center>
∀r ∈ ∆, Φ<sub>TOP</sub>(r) = {σ ∈ Σ<sub>T</sub> | ∃v ∈ R<sub>k,0</sub>(σ) : v ∈ Φ<sub>VERT</sub>(r)}
</center>



## 1.2 Encoding



# The Stellar Tree


# Implementation

I've developed a simple implementation in C++ to play with it.<br/>
[github]()

# Reference

- Fellegara, Riccardo, Weiss, Kenneth, De Floriani, Leila. The Stellar tree: a Compact Representation for Simplicial Complexes and Beyond[J].
