# Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`void `[`init_chain`](#chain_8h_1ac96eb7de4c8b1a7e3570d9200ef2cc8f)`(`[`Chain`](#struct_chain)` * chain)`            | Construct chain
`void `[`clear_chain`](#chain_8h_1aa4212f13a8d699b80b5c8fe4a5fab60b)`(`[`Chain`](#struct_chain)` * chain)`            | Clear chain
`void `[`append_cstr_to_chain`](#chain_8h_1ad442feef450b8b012044dfd726af81a8)`(`[`Chain`](#struct_chain)` * chain,const char * text)`            | Append a cstring to a chain
`void `[`append_flink_to_chain`](#chain_8h_1a2ae440a996132423425f5721b5c14d1b)`(`[`Chain`](#struct_chain)` * chain,`[`Fraction`](#struct_fraction)` fraction)`            | Append fraction as single [Link](#struct_link) to chain
`void `[`append_fraction_to_chain`](#chain_8h_1a116c3ec771d4a979a77eded5fdfc05a5)`(`[`Chain`](#struct_chain)` * chain,`[`Fraction`](#struct_fraction)` fraction)`            | Append fraction as string to chain
`void `[`append_chain_to_chain`](#chain_8h_1a902710243ebcd47c428a1dd41029ec2a)`(`[`Chain`](#struct_chain)` * chain1,`[`Chain`](#struct_chain)` chain2)`            | Append the contents in one chain to another
`void `[`append_stream_to_chain`](#chain_8h_1a05e36086654b1484594e617f0abf364b)`(`[`Chain`](#struct_chain)` * chain,FILE * stream)`            | Append the contents of a stream to a chain
`void `[`clear_stream`](#chain_8h_1a7380a3c04a041f4fb656497ff7a50510)`(FILE * stream)`            | Erase stream contents
`void `[`append_chain_to_stream`](#chain_8h_1aee4b1e3e6023ca24b3eb69187396b869)`(`[`Chain`](#struct_chain)` chain,FILE * stream)`            | Append chain to stream
`void `[`chain_to_stream`](#chain_8h_1aa3115ee4f4c5671ac35c33102fd3e2d0)`(`[`Chain`](#struct_chain)` chain,FILE * stream)`            | Assign chain to stream
`int `[`chain_to_cstr`](#chain_8h_1a784425b6bbc1c074e52e109871b526c0)`(`[`Chain`](#struct_chain)` chain,char * buffer)`            | Convert chain to cstring
`void `[`write_chain_to_file`](#chain_8h_1a897accbfb97acae9ff091b3dc13921c2)`(`[`Chain`](#struct_chain)` chain,`[`Chain`](#struct_chain)` filename)`            | Set file contents to chain's contents
`void `[`read_file_to_chain`](#chain_8h_1a008ca35b36cfa01cebd59a6dddd79671)`(`[`Chain`](#struct_chain)` * chain,`[`Chain`](#struct_chain)` filename)`            | Set chain contents to file's contents
`int `[`compare_chains`](#chain_8h_1aebea70af9ccbc3d25da67b8f836dba3d)`(`[`Chain`](#struct_chain)` a,`[`Chain`](#struct_chain)` b)`            | Compare chains
``[`Fraction`](#struct_fraction)` `[`chain_to_fraction`](#chain_8h_1ae351d3cf295fd95456e64cb1bb9216da)`(`[`Chain`](#struct_chain)` chain)`            | Convert chain to fraction
``[`Fraction`](#struct_fraction)` `[`get_next_byte_of_stream`](#chain_8h_1af64f25a456b3af7d9cbb635f6b56f20d)`(FILE * file)`            | 
`void `[`runtime_error`](#error_8h_1aa4581c050961a458136ec8bdd556d5b5)`(const char * msg,...)`            | Show error message and exit
``[`Fraction`](#struct_fraction)` `[`construct_fraction`](#fraction_8h_1affd36cedc3799420c2d6ddfbdbd81ddf)`(FractionInt num,FractionInt den)`            | Construct [Fraction](#struct_fraction)
`void `[`reduce_fraction`](#fraction_8h_1a945e863cbdcd274aef0eefb079d4b4d1)`(`[`Fraction`](#struct_fraction)` * a)`            | Reduce fraction to most basic form
``[`Fraction`](#struct_fraction)` `[`add_fractions`](#fraction_8h_1a61a421cc3f02c994922da7b24aa4c4e1)`(`[`Fraction`](#struct_fraction)` a,`[`Fraction`](#struct_fraction)` b)`            | Add two fractions
``[`Fraction`](#struct_fraction)` `[`subtract_fractions`](#fraction_8h_1aba98b22dcee1e4eb95a7ac2fe9281e8d)`(`[`Fraction`](#struct_fraction)` a,`[`Fraction`](#struct_fraction)` b)`            | Subtract two fractions
``[`Fraction`](#struct_fraction)` `[`multiply_fractions`](#fraction_8h_1a4b4e5ede06559519a9a6894aeef10526)`(`[`Fraction`](#struct_fraction)` a,`[`Fraction`](#struct_fraction)` b)`            | Multiply two fractions
``[`Fraction`](#struct_fraction)` `[`divide_fractions`](#fraction_8h_1a94da26ba38d24c1688e08a9d8d7ae6c8)`(`[`Fraction`](#struct_fraction)` a,`[`Fraction`](#struct_fraction)` b)`            | Divide two fractions
``[`Fraction`](#struct_fraction)` `[`modulus_fractions`](#fraction_8h_1a8b3e9f3e279ccb842a61ae8490c96959)`(`[`Fraction`](#struct_fraction)` a,`[`Fraction`](#struct_fraction)` b)`            | Modulus fractions
``[`Fraction`](#struct_fraction)` `[`factorial_fraction`](#fraction_8h_1a5a68b5e9f579eaf0e7ccc499fd55ab09)`(`[`Fraction`](#struct_fraction)` a)`            | Get factorial of fraction
`int `[`compare_fractions`](#fraction_8h_1a50c53ea17596e7cf28eb58aadd7042d2)`(`[`Fraction`](#struct_fraction)` a,`[`Fraction`](#struct_fraction)` b)`            | Compare fractions
``[`Fraction`](#struct_fraction)` `[`pow_fractions`](#fraction_8h_1afa5a6802e6d6acfa2ac36cabce0574a1)`(`[`Fraction`](#struct_fraction)` a,`[`Fraction`](#struct_fraction)` b)`            | Exponentiate fractions
`struct `[`Chain`](#struct_chain) | 
`struct `[`Fraction`](#struct_fraction) | 
`struct `[`Link`](#struct_link) | 

## Members

#### `void `[`init_chain`](#chain_8h_1ac96eb7de4c8b1a7e3570d9200ef2cc8f)`(`[`Chain`](#struct_chain)` * chain)` 

Construct chain

Set defaults for chain: length to 0 and start to NULL

#### Parameters
* `chain` The chain being constructed

#### `void `[`clear_chain`](#chain_8h_1aa4212f13a8d699b80b5c8fe4a5fab60b)`(`[`Chain`](#struct_chain)` * chain)` 

Clear chain

Free all links in chain and set start to NULL

#### Parameters
* `chain` The chain being cleared

#### `void `[`append_cstr_to_chain`](#chain_8h_1ad442feef450b8b012044dfd726af81a8)`(`[`Chain`](#struct_chain)` * chain,const char * text)` 

Append a cstring to a chain

Append each character of the cstring as a [Link](#struct_link) to the chain.

#### Parameters
* `chain` The chain being modified 

* `text` The string being added to the chain

#### `void `[`append_flink_to_chain`](#chain_8h_1a2ae440a996132423425f5721b5c14d1b)`(`[`Chain`](#struct_chain)` * chain,`[`Fraction`](#struct_fraction)` fraction)` 

Append fraction as single [Link](#struct_link) to chain

#### Parameters
* `chain` The chain being modified 

* `fraction` The fraction being added to the chain

#### `void `[`append_fraction_to_chain`](#chain_8h_1a116c3ec771d4a979a77eded5fdfc05a5)`(`[`Chain`](#struct_chain)` * chain,`[`Fraction`](#struct_fraction)` fraction)` 

Append fraction as string to chain

[Fraction](#struct_fraction) is first converted into a string format. For example, 25/1 would be converted to "twenty five" and then appended to the chain

#### Parameters
* `chain` The chain being modified 

* `fraction` The fraction being added to the chain

#### `void `[`append_chain_to_chain`](#chain_8h_1a902710243ebcd47c428a1dd41029ec2a)`(`[`Chain`](#struct_chain)` * chain1,`[`Chain`](#struct_chain)` chain2)` 

Append the contents in one chain to another

#### Parameters
* `chain1` The chain being modified 

* `chain2` The chain being appended to chain1

#### `void `[`append_stream_to_chain`](#chain_8h_1a05e36086654b1484594e617f0abf364b)`(`[`Chain`](#struct_chain)` * chain,FILE * stream)` 

Append the contents of a stream to a chain

Each char is read from the stream and copied to the chain as a fraction/Link.

#### Parameters
* `chain` The chain being modified 

* `stream` The stream whose contents are read

#### `void `[`clear_stream`](#chain_8h_1a7380a3c04a041f4fb656497ff7a50510)`(FILE * stream)` 

Erase stream contents

#### Parameters
* `stream` The stream being cleared

#### `void `[`append_chain_to_stream`](#chain_8h_1aee4b1e3e6023ca24b3eb69187396b869)`(`[`Chain`](#struct_chain)` chain,FILE * stream)` 

Append chain to stream

Print each fraction of chain to the stream to be appended as a char

#### Parameters
* `chain` The chain being read 

* `stream` The stream being appended to

#### `void `[`chain_to_stream`](#chain_8h_1aa3115ee4f4c5671ac35c33102fd3e2d0)`(`[`Chain`](#struct_chain)` chain,FILE * stream)` 

Assign chain to stream

Clear the stream, then call append_chain_to_stream

#### Parameters
* `chain` The chain being read 

* `stream` The stream being copied to

#### `int `[`chain_to_cstr`](#chain_8h_1a784425b6bbc1c074e52e109871b526c0)`(`[`Chain`](#struct_chain)` chain,char * buffer)` 

Convert chain to cstring

Print each fraction of chain to the cstring buffer to be appended as a char This function is not safe. If buffer is too small to hold the contents of chain, a segfault will occur

#### Parameters
* `chain` The chain being read 

* `buffer` The cstring being appended to 

#### Returns
The length of the buffer.

#### `void `[`write_chain_to_file`](#chain_8h_1a897accbfb97acae9ff091b3dc13921c2)`(`[`Chain`](#struct_chain)` chain,`[`Chain`](#struct_chain)` filename)` 

Set file contents to chain's contents

Open a file and set its contents to that of the chain's. As with other functions, each fraction is converted to a char. An error will be thrown upon any problem opening the file

#### Parameters
* `chain` The chain being read 

* `filename` A chain holding the filename of the file we're opening

#### `void `[`read_file_to_chain`](#chain_8h_1a008ca35b36cfa01cebd59a6dddd79671)`(`[`Chain`](#struct_chain)` * chain,`[`Chain`](#struct_chain)` filename)` 

Set chain contents to file's contents

Open a file and read its contents to the chain's, replacing any previous values(an assign, not append). As with other functions, each char is converted to a fraction. An error will be thrown upon any problem opening the file

#### Parameters
* `chain` The chain being overwritten 

* `filename` A chain holding the filename of the file we're opening

#### `int `[`compare_chains`](#chain_8h_1aebea70af9ccbc3d25da67b8f836dba3d)`(`[`Chain`](#struct_chain)` a,`[`Chain`](#struct_chain)` b)` 

Compare chains

Check if chains are equivalent. Will return 0 if they are, and another value if they are not.

#### Parameters
* `a` The first chain 

* `b` The second chain 

#### Returns
The comparison value

#### ``[`Fraction`](#struct_fraction)` `[`chain_to_fraction`](#chain_8h_1ae351d3cf295fd95456e64cb1bb9216da)`(`[`Chain`](#struct_chain)` chain)` 

Convert chain to fraction

Parse chain to convert to a fraction value. Return 0/1 if chain is invalid.

#### Parameters
* `chain` The chain being parsed 

#### Returns
The fraction value of the chain

#### ``[`Fraction`](#struct_fraction)` `[`get_next_byte_of_stream`](#chain_8h_1af64f25a456b3af7d9cbb635f6b56f20d)`(FILE * file)` 

#### `void `[`runtime_error`](#error_8h_1aa4581c050961a458136ec8bdd556d5b5)`(const char * msg,...)` 

Show error message and exit

Shows an error in the style of fprintf in red text, then exit with EXIT_FAILURE

#### Parameters
* `msg` The fprintf-style format string 

* `...` Any values referenced by the format string

#### ``[`Fraction`](#struct_fraction)` `[`construct_fraction`](#fraction_8h_1affd36cedc3799420c2d6ddfbdbd81ddf)`(FractionInt num,FractionInt den)` 

Construct [Fraction](#struct_fraction)

#### Parameters
* `num` The numerator 

* `den` The denominator 

#### Returns
The fraction constructed

#### `void `[`reduce_fraction`](#fraction_8h_1a945e863cbdcd274aef0eefb079d4b4d1)`(`[`Fraction`](#struct_fraction)` * a)` 

Reduce fraction to most basic form

#### Parameters
* `a` The fraction to be reduced

#### ``[`Fraction`](#struct_fraction)` `[`add_fractions`](#fraction_8h_1a61a421cc3f02c994922da7b24aa4c4e1)`(`[`Fraction`](#struct_fraction)` a,`[`Fraction`](#struct_fraction)` b)` 

Add two fractions

#### Parameters
* `a` The first fraction 

* `b` The second fraction 

#### Returns
a+b

#### ``[`Fraction`](#struct_fraction)` `[`subtract_fractions`](#fraction_8h_1aba98b22dcee1e4eb95a7ac2fe9281e8d)`(`[`Fraction`](#struct_fraction)` a,`[`Fraction`](#struct_fraction)` b)` 

Subtract two fractions

#### Parameters
* `a` The first fraction 

* `b` The second fraction 

#### Returns
a-b

#### ``[`Fraction`](#struct_fraction)` `[`multiply_fractions`](#fraction_8h_1a4b4e5ede06559519a9a6894aeef10526)`(`[`Fraction`](#struct_fraction)` a,`[`Fraction`](#struct_fraction)` b)` 

Multiply two fractions

#### Parameters
* `a` The first fraction 

* `b` The second fraction 

#### Returns
a*b

#### ``[`Fraction`](#struct_fraction)` `[`divide_fractions`](#fraction_8h_1a94da26ba38d24c1688e08a9d8d7ae6c8)`(`[`Fraction`](#struct_fraction)` a,`[`Fraction`](#struct_fraction)` b)` 

Divide two fractions

#### Parameters
* `a` The first fraction 

* `b` The second fraction 

#### Returns
a/b

#### ``[`Fraction`](#struct_fraction)` `[`modulus_fractions`](#fraction_8h_1a8b3e9f3e279ccb842a61ae8490c96959)`(`[`Fraction`](#struct_fraction)` a,`[`Fraction`](#struct_fraction)` b)` 

Modulus fractions

Get remainder after dividing two fractions. Throw an error if the fractions are non-integers

#### Parameters
* `a` The first fraction 

* `b` The second fraction 

#### Returns
ab

#### ``[`Fraction`](#struct_fraction)` `[`factorial_fraction`](#fraction_8h_1a5a68b5e9f579eaf0e7ccc499fd55ab09)`(`[`Fraction`](#struct_fraction)` a)` 

Get factorial of fraction

Return the factorial of a fraction. Throw an error if the fractions are non-integers

#### Parameters
* `a` The fraction to be factorialized 

#### Returns
a!

#### `int `[`compare_fractions`](#fraction_8h_1a50c53ea17596e7cf28eb58aadd7042d2)`(`[`Fraction`](#struct_fraction)` a,`[`Fraction`](#struct_fraction)` b)` 

Compare fractions

Return 0 if fractions are equal, -1 if a<b, and 1 if a>b

#### Parameters
* `a` The first fraction 

* `b` The second fraction 

#### Returns
The comparison result

#### ``[`Fraction`](#struct_fraction)` `[`pow_fractions`](#fraction_8h_1afa5a6802e6d6acfa2ac36cabce0574a1)`(`[`Fraction`](#struct_fraction)` a,`[`Fraction`](#struct_fraction)` b)` 

Exponentiate fractions

Return a to the bth power. This uses floating point math, so the answer will not be exact. Invalid arguments will throw an error.

#### Parameters
* `a` The first fraction 

* `b` The second fraction 

#### Returns
a^b

# struct `Chain` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`ChainLengthInt `[`length`](#struct_chain_1ae64f4a8b9dbb74363022186a1f144047) | 
``[`Link`](#struct_link)` * `[`start`](#struct_chain_1aebc021af7c08e2c738c00d126273fb7d) | 
``[`Link`](#struct_link)` * `[`end`](#struct_chain_1a9eee303efd53905eea33e45a17d9a1e7) | 

## Members

#### `ChainLengthInt `[`length`](#struct_chain_1ae64f4a8b9dbb74363022186a1f144047) 

#### ``[`Link`](#struct_link)` * `[`start`](#struct_chain_1aebc021af7c08e2c738c00d126273fb7d) 

#### ``[`Link`](#struct_link)` * `[`end`](#struct_chain_1a9eee303efd53905eea33e45a17d9a1e7) 

# struct `Fraction` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`FractionInt `[`num`](#struct_fraction_1a6c8a33596e97b6c6f8de71c1d9e673a3) | 
`FractionInt `[`den`](#struct_fraction_1ad4fff92faa36ed5197a3a10ca97519df) | 

## Members

#### `FractionInt `[`num`](#struct_fraction_1a6c8a33596e97b6c6f8de71c1d9e673a3) 

#### `FractionInt `[`den`](#struct_fraction_1ad4fff92faa36ed5197a3a10ca97519df) 

# struct `Link` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
``[`Fraction`](#struct_fraction)` `[`value`](#struct_link_1a398f21bd9c8db3bf5e788b0495bc623d) | 
`struct `[`Link`](#struct_link)` * `[`prev`](#struct_link_1af1e5687bdfac2994b98c23f359f4e0fd) | 
`struct `[`Link`](#struct_link)` * `[`next`](#struct_link_1a4c0511c20c869c43fda58d1eeeed7e73) | 

## Members

#### ``[`Fraction`](#struct_fraction)` `[`value`](#struct_link_1a398f21bd9c8db3bf5e788b0495bc623d) 

#### `struct `[`Link`](#struct_link)` * `[`prev`](#struct_link_1af1e5687bdfac2994b98c23f359f4e0fd) 

#### `struct `[`Link`](#struct_link)` * `[`next`](#struct_link_1a4c0511c20c869c43fda58d1eeeed7e73) 

Generated by [Moxygen](https://sourcey.com/moxygen)