<h1>INTRODUCTION</h1>

Working with biological data (e.g. protein sequences, genomic sequences, etc) in an efficient manner is at the heart of computational biology and bioinformatics.  Consider the human genome and its roughly 3 billion base pairs (that is, 3 billion characters in the set {ATCG}, not including wildcard characters); without the right data structures and algorithms, processing and utilizing a genome becomes a painfully long, expensive task.  Fortunately, because these datasets are simply very long strings, there are a number of structures and algorithms available that usher in practicality to this space.  In particular, the suffix array has become a popular structure for solving biological problems in space- and time-effective ways.  Herein, I will explain the basic properties of suffix arrays, present a comparative analysis between them and related structures, outline some of the biological problems they solve, and describe steps I’ve taken in constructing my own implementation of one.

<h2>HOW TO USE THIS APPLICATION</h2>

The main features of this implementation of a suffix array are searching for
substrings within the original text used to construct the suffix array.

<code>Usage: ./suffix_array_main <filename></code>

The format of the data will be important for accurate search of the suffix
suffix array.  The expected format is a single line of lower-case characters
(i.e. no line breaks).  Note, feel free to deviate from this format; however,
pay attention to perform defects.

What's more, if working with genetic data, note that this implementation is
for local, non-gapped, exact sequences, so if not working with sequences
made exclusively of characters in the set {a,c,t,g}, pay attention to
performance.

Features:
    - Search Exact
    - Find All Exact
    - Search Inexact (using a mismatch threshold)
    - Find All Inexact

    - All of these methods can be augmented by searching for reversed and/or complemented sequences (latter option only viable for genetic sequences).

<h3>SUFFIX ARRAY BASICS</h3>

The suffix array is a data structure with the ability to solve famous string-based computational problems like pattern matching, long common substring between two strings, and longest palindromic sequence amongst others.  To understand suffix arrays, one must first understand strings and suffixes.  A string, for our purposes, is a collection of alphanumeric symbols (encoded using a particular schema such as ASCII), and suffixes are the substrings generated from a string by removing one letter at a time.  For example, the string “banana” is broken down into the suffixes {“banana”, “anana”, “nana”, “ana”, “na”, “a”}.  A suffix array takes these suffixes and sorts them lexographically:  {“a”, “ana”, “anana”, “banana”, “na”, “nana”} producing an array of the sorted indices (based on the index of the first letter of the suffix), [5, 3, 1, 0, 4, 2].  A proper suffix array structure may contain more information than the array itself; however, this simple array is the foundation for all suffix arrays and forms the basis for solving string-/biology-related problems.

<h3>CANNONICAL APPLICATIONS</h3>

The first and, arguably, most important application for a suffix array in computational biology is pattern matching; that is finding a specified sequence of characters in a larger text.  For example, given genomic data, we may want to know if a particular gene or gene variation is present.  In addition to just finding if a pattern exists in the text, it may be helpful to find where the pattern exists and/or how many times it appears.  A number of other important biology-subproblem-solutions exist using a suffix array.  Without going into the details of genome sequence construction, a vital problem to be solved is known as the longest common substring problem, which can be solved efficiently by a suffix array.  These applications are discussed further later.

<h3>COMPARATIVE ANALYSIS</h3>

It should be noted that the suffix array is not the only data structure or collection of algorithms that can solve these problems.  In fact, there are a number of algorithms and other data structures that can handle them.  So, why the suffix array?  First, let’s consider an algorithm for string pattern matching:  Knuth-Morris-Pratt algorithm (KMP).  This famous algorithm is able to solve pattern matching O(m*n) time (including pattern preprocessing), where m is the length of the pattern and n is the length of the text.  This sounds pretty good, especially considering that constructing a suffix tree is going to be at best O(n) and searching that tree will be O(m); therefore, when doing both, we end up back at O(m*n).  Therein lies the advantage though.  With the suffix array, we only need to perform construction once, so if we are looking for many patterns in a particular text, we can keep running them with complexity of O(m) (which can be orders of magnitude smaller than KMP’s O(m*n) for large texts).

What about other data structures?  The suffix array is actually an extended form of the suffix trie and suffix tree.  These data structures (particularly the suffix tree) are efficient at solving these string-based problems as well, and in some cases make for easier implementation of the methods.  However, these data structures are very costly in terms of space requirements—the suffix tree increases the amount of information of the original text 10-20 fold, and it only gets worse for the suffix trie (which is essentially the uncompressed form a suffix tree) (Shrestha, 2014).  A suffix tree, on the other hand, will increase the amount of information of the original text by approximately 8-fold.  This space requirement can become very important when working with large datasets, such as genomic data.

<h3>CONCLUSION</h3>

At first glance, the suffix array may seem like a very simple data structure with few applications; however, as demonstrated, it contains the unique combination of space- and time-efficient solutions to common string problems (lending to its popularity in the computational biology field).  The functions associated with this data structure range from trivial to multi-stepped and difficult, making it an interesting structure for a burgeoning computational biologist to attempt to implement (helping the student learn the necessity of performance in the context of biological problems).  Without suffix arrays (or the related suffix tree/trie) many applications of computational biology may still lie in the theoretical realm; therefore, their importance should not be understated.

<h3>REFERENCES</h3>

Shrestha, A. M. S., Frith, M. C., & Horton, P. (2014). A bioinformatician’s guide to the forefront of suffix array construction algorithms. Briefings in bioinformatics, 15(2), 138-154.

Vladu, A., & Negruşeri, C. (2005). Suffix arrays–a programming contest approach.
