---
layout: post
title: 读论文_The Stellar Tree
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
<img src = "https://raw.githubusercontent.com/v1otusc/PicBed/master/vert_mapping_function.png" width = "60%">
</center>

Formally, Φ<sub>TOP</sub> is a function from the regions of ∆ to the powerset of Σ<sub>T</sub>:

<center>
∀r ∈ ∆, Φ<sub>TOP</sub>(r) = {σ ∈ Σ<sub>T</sub> | ∃v ∈ R<sub>k,0</sub>(σ) : v ∈ Φ<sub>VERT</sub>(r)}
</center>

> k is the dimension of top cells.

below is an example of mapping function Φ<sub>TOP</sub>, for two regions (blue rectangles) of the decomposition of Figure 1(b) on a triangle mesh defined over its vertices. 

<center>
<img src = "https://raw.githubusercontent.com/v1otusc/PicBed/master/topcells_mapping_function.png" >
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

A detailed description of a Stellar decomposition of data structures **for representing a CP complex** and a compressed encoding **for the regions of the decomposition**.

### 1.2.1 Indexed representation of the CP complex

Assume that the underlying CP complex is representedas an indexed complex, which encodes the spatial position of the vertices and the boundary relation R<sub>k,0</sub> of each top k-simplex in Σ.

We use an array-based representation for the verticesand top cells of Σ. The Σ<sub>V</sub> array encodes the position of each vertex v in Σ, requiring a total of n·\| Σ<sub>V</sub> \| coordinates. 

Then consider the boundary relation, The top CP cells are encoded using separate arrays Σ<sub>T<sub>k</sub></sub> for each dimension k ≤ d that has top CP cells in Σ. Σ<sub>T<sub>k</sub></sub> encodes the boundary connectivity from its top CP cells to their vertices, i.e., relation R<sub>k,0</sub> in terms of the indices of the vertices of its cells within Σ<sub>V</sub>. This requires \|R<sub>k,0</sub>(σ)\| references for a top k-cell σ. e.g. (k+1) vertex indices for a k-simplex and 2<sup>k</sup> references for a k-cube.

**Thus**, the total storage cost of the indexed mesh representation is:

<center>
n·|Σ<sub>V</sub>| + ∑<sub>k=1 -> d</sub>∑<sub>σ ∈ Σ<sub>T<sub>k</sub></sub></sub> |R<sub>k,0</sub>(σ)|
</center>

Note that, in typical cases, where Σ is *pure* (i.e., its top CP cells all have the same dimension d), Σ requires only two arrays: one for the vertices and one for the top cells.

### 1.2.2 A compressed region representation

**Consider two encoding strategies** for the data mapped to each region of the decomposition.

**First** is a simple strategy that explicitly encodes the arrays of vertices and top CP cells **mapped** to each region and work our way to a compressed representation of these lists. Under Φ, each region r in ∆ maps to a list of vertices r<sub>V</sub> and a list of top CP cells r<sub>T</sub> from the complex Σ. A straightforward strategy would be to encode lists of vertices and top CP cells that explicitly list the mapped elements for each region r. We refer to this as the EXPLICIT Stellar decomposition encoding.

<center>
<img src = "https://raw.githubusercontent.com/v1otusc/PicBed/master/Explicit_stellar_decomposition.png" width = "70%">
</center>

The above encoding can be very expensive due to the redundant encoding of **top CP cells with vertices in multiple regions**.

**Second** is a COMPRESSED Stellar decomposition encoding that compacts the vertex and top CP cells lists in each region r by exploiting the *locality* of the elements within r. By replacing *runs* of incrementing consecutive sequences of indices using a generalization of *run-length encoding* **(RLE)[Held and Marshall, 1991]**. RLE is a form of data compression in which *runs* of consecutive identical values are encoded as pairs of integers representing the value and repetition count, rather than as multiple copies of the original value. 

<center>
<img src = "https://raw.githubusercontent.com/v1otusc/PicBed/master/runlength_and_sequentialrange.png" width = "70%">
</center>

For example, in the figure.a above the four entries with value '2' are compacted into a pair of entries \[-2,4\], where a negative first number indicates the start of a run and its value, while the second number indicates the run’s length. 

While we **do not** have such duplicated runs in our indexed representation, we often have *incrementing sequences* of indexes, such as {40,41,42,43,44}, within a local vertex list r<sub>V</sub> or top CP cells list r<sub>T</sub>. We therefore refer to a generalized RLE Scheme as **Sequential Range Encoding (SRE)** to compress such sequence : *the incrementing sequences*. SRE encodes a *run* of **consecutive non-negative indexes** using a pair of integers, representing the starting index, and the number of remaining elements in the range. As with RLE, we can intersperse runs (sequences) with non-runs in the same list by negating the starting index of a run. Thus, it is easy to determine whether or not we are in a run while we iterate through a sequential range encoded list. A feature of this scheme is that it allows us to dynamically append individual elements or runs to an SRE list with no storage overhead. Furthermore, we can easily expand a compacted range by replacing its entries with the first two values of the range **and appending the remaining values to the end of the list**. 

> An ERROR in the figure.b above ?, the sequence {10, 11, 12} should be represented with the pair [-10, 2], use 2 to represent **the remain**, or we can replace 14 by 13.

We then introducea a global characteristic that measures the average storage requirements for a top CP cell in a Stellar decomposition representation.

**Definition: average reference number**

The average reference number μ of a Stellar decomposition is the average number of references required to encode a top CP cell in the r<sub>T</sub> lists of the regions in ∆. Formally:

<center>
μ = ( ∑<sub>r ∈ ∆</sub>|r<sub>T</sub>| ) / |Σ<sub>T</sub>|
</center>

**where \|r<sub>T</sub>\| is the size of the top CP cells list in a region r**.

An EXPLICIT representation is equivalent to a COMPRESSED representation without any compressed runs, thus, it is always the case that μ ≤ χ (the average spanning number). 

<center>
<img src = "https://raw.githubusercontent.com/v1otusc/PicBed/master/compressed_encoding.png" width = "70%">
</center>

Figure above illustrates a COMPRESSED representation of the mesh from the **third Figure** after its vertex and triangle arrays have been reordered (in an external process) and highlights its sequential ranges, where r<sub>V</sub> requires a single run to encode the indexed vertices and r<sub>T</sub> requires four sequential runs to encode the indices of its triangles.

# The Stellar Tree

The Stellar decomposition is a *general* model that is *agnostic* about how the decomposition is attained and about its relationship to the underlying CP complex. Thus, 

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
