# Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public void `[`init_chain`](#chain_8h_1ac96eb7de4c8b1a7e3570d9200ef2cc8f)`(`[`Chain`](#struct_chain)` * chain)`            | Construct chain
`public void `[`clear_chain`](#chain_8h_1aa4212f13a8d699b80b5c8fe4a5fab60b)`(`[`Chain`](#struct_chain)` * chain)`            | Clear chain
`public void `[`append_cstr_to_chain`](#chain_8h_1ad442feef450b8b012044dfd726af81a8)`(`[`Chain`](#struct_chain)` * chain,const char * text)`            | Append a cstring to a chain
`public void `[`append_flink_to_chain`](#chain_8h_1a2ae440a996132423425f5721b5c14d1b)`(`[`Chain`](#struct_chain)` * chain,`[`Fraction`](#struct_fraction)` fraction)`            | Append fraction as single [Link](#struct_link) to chain
`public void `[`append_fraction_to_chain`](#chain_8h_1a116c3ec771d4a979a77eded5fdfc05a5)`(`[`Chain`](#struct_chain)` * chain,`[`Fraction`](#struct_fraction)` fraction)`            | Append fraction as string to chain
`public void `[`append_chain_to_chain`](#chain_8h_1a902710243ebcd47c428a1dd41029ec2a)`(`[`Chain`](#struct_chain)` * chain1,`[`Chain`](#struct_chain)` chain2)`            | Append the contents in one chain to another
`public void `[`append_stream_to_chain`](#chain_8h_1a05e36086654b1484594e617f0abf364b)`(`[`Chain`](#struct_chain)` * chain,FILE * stream)`            | Append the contents of a stream to a chain
`public void `[`chain_to_stream`](#chain_8h_1aa3115ee4f4c5671ac35c33102fd3e2d0)`(`[`Chain`](#struct_chain)` chain,FILE * stream)`            | Copy chain to stream
`public int `[`chain_to_cstr`](#chain_8h_1a784425b6bbc1c074e52e109871b526c0)`(`[`Chain`](#struct_chain)` chain,char * buffer)`            | Convert chain to cstring
`public void `[`write_chain_to_file`](#chain_8h_1a897accbfb97acae9ff091b3dc13921c2)`(`[`Chain`](#struct_chain)` chain,`[`Chain`](#struct_chain)` filename)`            | Set file contents to chain's contents
`public void `[`read_file_to_chain`](#chain_8h_1a008ca35b36cfa01cebd59a6dddd79671)`(`[`Chain`](#struct_chain)` * chain,`[`Chain`](#struct_chain)` filename)`            | Set chain contents to file's contents
`public int `[`compare_chains`](#chain_8h_1aebea70af9ccbc3d25da67b8f836dba3d)`(`[`Chain`](#struct_chain)` a,`[`Chain`](#struct_chain)` b)`            | Compare chains
`public `[`Fraction`](#struct_fraction)` `[`chain_to_fraction`](#chain_8h_1ae351d3cf295fd95456e64cb1bb9216da)`(`[`Chain`](#struct_chain)` chain)`            | Convert chain to fraction
`public void `[`runtime_error`](#error_8h_1aa4581c050961a458136ec8bdd556d5b5)`(const char * msg,...)`            | Show error message and exit
`public `[`Fraction`](#struct_fraction)` `[`construct_fraction`](#fraction_8h_1affd36cedc3799420c2d6ddfbdbd81ddf)`(FractionInt num,FractionInt den)`            | Construct [Fraction](#struct_fraction)
`public `[`Fraction`](#struct_fraction)` `[`random_fraction`](#fraction_8h_1aff0108be8808ee831aaac374030930b4)`()`            | 
`public `[`Fraction`](#struct_fraction)` `[`cryptorandom_fraction`](#fraction_8h_1a78d8f5be26e020fd33f5928b2aaf36b1)`()`            | 
`public `[`Fraction`](#struct_fraction)` `[`time_fraction`](#fraction_8h_1a1287cf8ca974a6713dd6af32e2016524)`()`            | 
`public void `[`reduce_fraction`](#fraction__math_8h_1a945e863cbdcd274aef0eefb079d4b4d1)`(`[`Fraction`](#struct_fraction)` * a)`            | 
`public `[`Fraction`](#struct_fraction)` `[`add_fractions`](#fraction__math_8h_1a61a421cc3f02c994922da7b24aa4c4e1)`(`[`Fraction`](#struct_fraction)` a,`[`Fraction`](#struct_fraction)` b)`            | 
`public `[`Fraction`](#struct_fraction)` `[`subtract_fractions`](#fraction__math_8h_1aba98b22dcee1e4eb95a7ac2fe9281e8d)`(`[`Fraction`](#struct_fraction)` a,`[`Fraction`](#struct_fraction)` b)`            | 
`public `[`Fraction`](#struct_fraction)` `[`multiply_fractions`](#fraction__math_8h_1a4b4e5ede06559519a9a6894aeef10526)`(`[`Fraction`](#struct_fraction)` a,`[`Fraction`](#struct_fraction)` b)`            | 
`public `[`Fraction`](#struct_fraction)` `[`divide_fractions`](#fraction__math_8h_1a94da26ba38d24c1688e08a9d8d7ae6c8)`(`[`Fraction`](#struct_fraction)` a,`[`Fraction`](#struct_fraction)` b)`            | 
`public `[`Fraction`](#struct_fraction)` `[`modulus_fractions`](#fraction__math_8h_1a8b3e9f3e279ccb842a61ae8490c96959)`(`[`Fraction`](#struct_fraction)` a,`[`Fraction`](#struct_fraction)` b)`            | 
`public `[`Fraction`](#struct_fraction)` `[`factorial_fraction`](#fraction__math_8h_1a5a68b5e9f579eaf0e7ccc499fd55ab09)`(`[`Fraction`](#struct_fraction)` a)`            | 
`public int `[`compare_fractions`](#fraction__math_8h_1a50c53ea17596e7cf28eb58aadd7042d2)`(`[`Fraction`](#struct_fraction)` a,`[`Fraction`](#struct_fraction)` b)`            | 
`public `[`Fraction`](#struct_fraction)` `[`pow_fractions`](#fraction__math_8h_1afa5a6802e6d6acfa2ac36cabce0574a1)`(`[`Fraction`](#struct_fraction)` a,`[`Fraction`](#struct_fraction)` b)`            | 
`struct `[`Chain`](#struct_chain) | 
`struct `[`Fraction`](#struct_fraction) | 
`struct `[`Link`](#struct_link) | 

## Members

#### `public void `[`init_chain`](#chain_8h_1ac96eb7de4c8b1a7e3570d9200ef2cc8f)`(`[`Chain`](#struct_chain)` * chain)` 

Construct chain

Set defaults for chain: length to 0 and start to NULL

#### Parameters
* `chain` The chain being constructed

#### `public void `[`clear_chain`](#chain_8h_1aa4212f13a8d699b80b5c8fe4a5fab60b)`(`[`Chain`](#struct_chain)` * chain)` 

Clear chain

Free all links in chain and set start to NULL

#### Parameters
* `chain` The chain being cleared

#### `public void `[`append_cstr_to_chain`](#chain_8h_1ad442feef450b8b012044dfd726af81a8)`(`[`Chain`](#struct_chain)` * chain,const char * text)` 

Append a cstring to a chain

Append each character of the cstring as a [Link](#struct_link) to the chain.

#### Parameters
* `chain` The chain being modified 

* `text` The string being added to the chain

#### `public void `[`append_flink_to_chain`](#chain_8h_1a2ae440a996132423425f5721b5c14d1b)`(`[`Chain`](#struct_chain)` * chain,`[`Fraction`](#struct_fraction)` fraction)` 

Append fraction as single [Link](#struct_link) to chain

#### Parameters
* `chain` The chain being modified 

* `fraction` The fraction being added to the chain

#### `public void `[`append_fraction_to_chain`](#chain_8h_1a116c3ec771d4a979a77eded5fdfc05a5)`(`[`Chain`](#struct_chain)` * chain,`[`Fraction`](#struct_fraction)` fraction)` 

Append fraction as string to chain

[Fraction](#struct_fraction) is first converted into a string format. For example, 25/1 would be converted to "twenty five" and then appended to the chain

#### Parameters
* `chain` The chain being modified 

* `fraction` The fraction being added to the chain

#### `public void `[`append_chain_to_chain`](#chain_8h_1a902710243ebcd47c428a1dd41029ec2a)`(`[`Chain`](#struct_chain)` * chain1,`[`Chain`](#struct_chain)` chain2)` 

Append the contents in one chain to another

#### Parameters
* `chain1` The chain being modified 

* `chain2` The chain being appended to chain1

#### `public void `[`append_stream_to_chain`](#chain_8h_1a05e36086654b1484594e617f0abf364b)`(`[`Chain`](#struct_chain)` * chain,FILE * stream)` 

Append the contents of a stream to a chain

Each char is read from the stream and copied to the chain as a fraction/Link.

#### Parameters
* `chain` The chain being modified 

* `stream` The stream whose contents are read

#### `public void `[`chain_to_stream`](#chain_8h_1aa3115ee4f4c5671ac35c33102fd3e2d0)`(`[`Chain`](#struct_chain)` chain,FILE * stream)` 

Copy chain to stream

Print each fraction of chain to the stream to be appended as a char

#### Parameters
* `chain` The chain being read 

* `stream` The stream being appended to

#### `public int `[`chain_to_cstr`](#chain_8h_1a784425b6bbc1c074e52e109871b526c0)`(`[`Chain`](#struct_chain)` chain,char * buffer)` 

Convert chain to cstring

Print each fraction of chain to the cstring buffer to be appended as a char This function is not safe. If buffer is too small to hold the contents of chain, a segfault will occur

#### Parameters
* `chain` The chain being read 

* `buffer` The cstring being appended to 

#### Returns
The length of the buffer.

#### `public void `[`write_chain_to_file`](#chain_8h_1a897accbfb97acae9ff091b3dc13921c2)`(`[`Chain`](#struct_chain)` chain,`[`Chain`](#struct_chain)` filename)` 

Set file contents to chain's contents

Open a file and set its contents to that of the chain's. As with other functions, each fraction is converted to a char. An error will be thrown upon any problem opening the file

#### Parameters
* `chain` The chain being read 

* `filename` A chain holding the filename of the file we're opening

#### `public void `[`read_file_to_chain`](#chain_8h_1a008ca35b36cfa01cebd59a6dddd79671)`(`[`Chain`](#struct_chain)` * chain,`[`Chain`](#struct_chain)` filename)` 

Set chain contents to file's contents

Open a file and read its contents to the chain's, replacing any previous values(an assign, not append). As with other functions, each char is converted to a fraction. An error will be thrown upon any problem opening the file

#### Parameters
* `chain` The chain being overwritten 

* `filename` A chain holding the filename of the file we're opening

#### `public int `[`compare_chains`](#chain_8h_1aebea70af9ccbc3d25da67b8f836dba3d)`(`[`Chain`](#struct_chain)` a,`[`Chain`](#struct_chain)` b)` 

Compare chains

Check if chaims are equivalent. Will return 0 if they are, and another value if they are not.

#### Parameters
* `a` The first chain 

* `b` The second chain 

#### Returns
The comparison value

#### `public `[`Fraction`](#struct_fraction)` `[`chain_to_fraction`](#chain_8h_1ae351d3cf295fd95456e64cb1bb9216da)`(`[`Chain`](#struct_chain)` chain)` 

Convert chain to fraction

Parse chain to convert to a fraction value. Return 0/1 if chain is invalid.

#### Parameters
* `chain` The chain being parsed 

#### Returns
The fraction value of the chain

#### `public void `[`runtime_error`](#error_8h_1aa4581c050961a458136ec8bdd556d5b5)`(const char * msg,...)` 

Show error message and exit

Shows an error in the style of fprintf in red text, then exit with EXIT_FAILURE

#### Parameters
* `msg` The fprintf-style format string 

* `...` Any values referenced by the format string

#### `public `[`Fraction`](#struct_fraction)` `[`construct_fraction`](#fraction_8h_1affd36cedc3799420c2d6ddfbdbd81ddf)`(FractionInt num,FractionInt den)` 

Construct [Fraction](#struct_fraction)

#### Parameters
* `num` The numerator 

* `den` The denominator 

#### Returns
The fraction constructed

#### `public `[`Fraction`](#struct_fraction)` `[`random_fraction`](#fraction_8h_1aff0108be8808ee831aaac374030930b4)`()` 

#### `public `[`Fraction`](#struct_fraction)` `[`cryptorandom_fraction`](#fraction_8h_1a78d8f5be26e020fd33f5928b2aaf36b1)`()` 

#### `public `[`Fraction`](#struct_fraction)` `[`time_fraction`](#fraction_8h_1a1287cf8ca974a6713dd6af32e2016524)`()` 

#### `public void `[`reduce_fraction`](#fraction__math_8h_1a945e863cbdcd274aef0eefb079d4b4d1)`(`[`Fraction`](#struct_fraction)` * a)` 

#### `public `[`Fraction`](#struct_fraction)` `[`add_fractions`](#fraction__math_8h_1a61a421cc3f02c994922da7b24aa4c4e1)`(`[`Fraction`](#struct_fraction)` a,`[`Fraction`](#struct_fraction)` b)` 

#### `public `[`Fraction`](#struct_fraction)` `[`subtract_fractions`](#fraction__math_8h_1aba98b22dcee1e4eb95a7ac2fe9281e8d)`(`[`Fraction`](#struct_fraction)` a,`[`Fraction`](#struct_fraction)` b)` 

#### `public `[`Fraction`](#struct_fraction)` `[`multiply_fractions`](#fraction__math_8h_1a4b4e5ede06559519a9a6894aeef10526)`(`[`Fraction`](#struct_fraction)` a,`[`Fraction`](#struct_fraction)` b)` 

#### `public `[`Fraction`](#struct_fraction)` `[`divide_fractions`](#fraction__math_8h_1a94da26ba38d24c1688e08a9d8d7ae6c8)`(`[`Fraction`](#struct_fraction)` a,`[`Fraction`](#struct_fraction)` b)` 

#### `public `[`Fraction`](#struct_fraction)` `[`modulus_fractions`](#fraction__math_8h_1a8b3e9f3e279ccb842a61ae8490c96959)`(`[`Fraction`](#struct_fraction)` a,`[`Fraction`](#struct_fraction)` b)` 

#### `public `[`Fraction`](#struct_fraction)` `[`factorial_fraction`](#fraction__math_8h_1a5a68b5e9f579eaf0e7ccc499fd55ab09)`(`[`Fraction`](#struct_fraction)` a)` 

#### `public int `[`compare_fractions`](#fraction__math_8h_1a50c53ea17596e7cf28eb58aadd7042d2)`(`[`Fraction`](#struct_fraction)` a,`[`Fraction`](#struct_fraction)` b)` 

#### `public `[`Fraction`](#struct_fraction)` `[`pow_fractions`](#fraction__math_8h_1afa5a6802e6d6acfa2ac36cabce0574a1)`(`[`Fraction`](#struct_fraction)` a,`[`Fraction`](#struct_fraction)` b)` 

# struct `Chain` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public ChainLengthInt `[`length`](#struct_chain_1ae64f4a8b9dbb74363022186a1f144047) | 
`public `[`Link`](#struct_link)` * `[`start`](#struct_chain_1aebc021af7c08e2c738c00d126273fb7d) | 
`public `[`Link`](#struct_link)` * `[`end`](#struct_chain_1a9eee303efd53905eea33e45a17d9a1e7) | 

## Members

#### `public ChainLengthInt `[`length`](#struct_chain_1ae64f4a8b9dbb74363022186a1f144047) 

#### `public `[`Link`](#struct_link)` * `[`start`](#struct_chain_1aebc021af7c08e2c738c00d126273fb7d) 

#### `public `[`Link`](#struct_link)` * `[`end`](#struct_chain_1a9eee303efd53905eea33e45a17d9a1e7) 

# struct `Fraction` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public FractionInt `[`num`](#struct_fraction_1a6c8a33596e97b6c6f8de71c1d9e673a3) | 
`public FractionInt `[`den`](#struct_fraction_1ad4fff92faa36ed5197a3a10ca97519df) | 

## Members

#### `public FractionInt `[`num`](#struct_fraction_1a6c8a33596e97b6c6f8de71c1d9e673a3) 

#### `public FractionInt `[`den`](#struct_fraction_1ad4fff92faa36ed5197a3a10ca97519df) 

# struct `Link` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public `[`Fraction`](#struct_fraction)` `[`value`](#struct_link_1a398f21bd9c8db3bf5e788b0495bc623d) | 
`public struct `[`Link`](#struct_link)` * `[`prev`](#struct_link_1af1e5687bdfac2994b98c23f359f4e0fd) | 
`public struct `[`Link`](#struct_link)` * `[`next`](#struct_link_1a4c0511c20c869c43fda58d1eeeed7e73) | 

## Members

#### `public `[`Fraction`](#struct_fraction)` `[`value`](#struct_link_1a398f21bd9c8db3bf5e788b0495bc623d) 

#### `public struct `[`Link`](#struct_link)` * `[`prev`](#struct_link_1af1e5687bdfac2994b98c23f359f4e0fd) 

#### `public struct `[`Link`](#struct_link)` * `[`next`](#struct_link_1a4c0511c20c869c43fda58d1eeeed7e73) 

Generated by [Moxygen](https://sourcey.com/moxygen)