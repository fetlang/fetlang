# Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public void `[`init_chain`](#chain_8h_1ac96eb7de4c8b1a7e3570d9200ef2cc8f)`(`[`Chain`](#struct_orgy_chain_structure)` * chain)`            | Construct chain
`public void `[`clear_chain`](#chain_8h_1aa4212f13a8d699b80b5c8fe4a5fab60b)`(`[`Chain`](#struct_orgy_chain_structure)` * chain)`            | Clear chain
`public void `[`append_cstr_to_chain`](#chain_8h_1ad442feef450b8b012044dfd726af81a8)`(`[`Chain`](#struct_orgy_chain_structure)` * chain,const char * text)`            | 
`public void `[`append_flink_to_chain`](#chain_8h_1a2ae440a996132423425f5721b5c14d1b)`(`[`Chain`](#struct_orgy_chain_structure)` * chain,`[`Fraction`](#struct_orgy_fraction_structure)` fraction)`            | 
`public void `[`append_fraction_to_chain`](#chain_8h_1a116c3ec771d4a979a77eded5fdfc05a5)`(`[`Chain`](#struct_orgy_chain_structure)` * chain,`[`Fraction`](#struct_orgy_fraction_structure)` fraction)`            | 
`public void `[`append_chain_to_chain`](#chain_8h_1a902710243ebcd47c428a1dd41029ec2a)`(`[`Chain`](#struct_orgy_chain_structure)` * chain1,`[`Chain`](#struct_orgy_chain_structure)` chain2)`            | 
`public void `[`append_stream_to_chain`](#chain_8h_1a05e36086654b1484594e617f0abf364b)`(`[`Chain`](#struct_orgy_chain_structure)` * chain,FILE * stream)`            | 
`public void `[`chain_to_stream`](#chain_8h_1aa3115ee4f4c5671ac35c33102fd3e2d0)`(`[`Chain`](#struct_orgy_chain_structure)` chain,FILE * stream)`            | 
`public int `[`chain_to_cstr`](#chain_8h_1a784425b6bbc1c074e52e109871b526c0)`(`[`Chain`](#struct_orgy_chain_structure)` chain,char * buffer)`            | 
`public void `[`write_chain_to_file`](#chain_8h_1a897accbfb97acae9ff091b3dc13921c2)`(`[`Chain`](#struct_orgy_chain_structure)` chain,`[`Chain`](#struct_orgy_chain_structure)` filename)`            | 
`public void `[`read_file_to_chain`](#chain_8h_1a008ca35b36cfa01cebd59a6dddd79671)`(`[`Chain`](#struct_orgy_chain_structure)` * chain,`[`Chain`](#struct_orgy_chain_structure)` filename)`            | 
`public int `[`compare_chains`](#chain_8h_1aebea70af9ccbc3d25da67b8f836dba3d)`(`[`Chain`](#struct_orgy_chain_structure)` a,`[`Chain`](#struct_orgy_chain_structure)` b)`            | 
`public `[`Fraction`](#struct_orgy_fraction_structure)` `[`chain_to_fraction`](#chain_8h_1ae351d3cf295fd95456e64cb1bb9216da)`(`[`Chain`](#struct_orgy_chain_structure)` chain)`            | 
`public void `[`runtime_error`](#error_8h_1aa4581c050961a458136ec8bdd556d5b5)`(const char * msg,...)`            | Show error message and exit
`public `[`Fraction`](#struct_orgy_fraction_structure)` `[`construct_fraction`](#fraction_8h_1affd36cedc3799420c2d6ddfbdbd81ddf)`(FractionInt num,FractionInt den)`            | 
`public `[`Fraction`](#struct_orgy_fraction_structure)` `[`random_fraction`](#fraction_8h_1aff0108be8808ee831aaac374030930b4)`()`            | 
`public `[`Fraction`](#struct_orgy_fraction_structure)` `[`cryptorandom_fraction`](#fraction_8h_1a78d8f5be26e020fd33f5928b2aaf36b1)`()`            | 
`public `[`Fraction`](#struct_orgy_fraction_structure)` `[`time_fraction`](#fraction_8h_1a1287cf8ca974a6713dd6af32e2016524)`()`            | 
`public void `[`reduce_fraction`](#fraction__math_8h_1a945e863cbdcd274aef0eefb079d4b4d1)`(`[`Fraction`](#struct_orgy_fraction_structure)` * a)`            | 
`public `[`Fraction`](#struct_orgy_fraction_structure)` `[`add_fractions`](#fraction__math_8h_1a61a421cc3f02c994922da7b24aa4c4e1)`(`[`Fraction`](#struct_orgy_fraction_structure)` a,`[`Fraction`](#struct_orgy_fraction_structure)` b)`            | 
`public `[`Fraction`](#struct_orgy_fraction_structure)` `[`subtract_fractions`](#fraction__math_8h_1aba98b22dcee1e4eb95a7ac2fe9281e8d)`(`[`Fraction`](#struct_orgy_fraction_structure)` a,`[`Fraction`](#struct_orgy_fraction_structure)` b)`            | 
`public `[`Fraction`](#struct_orgy_fraction_structure)` `[`multiply_fractions`](#fraction__math_8h_1a4b4e5ede06559519a9a6894aeef10526)`(`[`Fraction`](#struct_orgy_fraction_structure)` a,`[`Fraction`](#struct_orgy_fraction_structure)` b)`            | 
`public `[`Fraction`](#struct_orgy_fraction_structure)` `[`divide_fractions`](#fraction__math_8h_1a94da26ba38d24c1688e08a9d8d7ae6c8)`(`[`Fraction`](#struct_orgy_fraction_structure)` a,`[`Fraction`](#struct_orgy_fraction_structure)` b)`            | 
`public `[`Fraction`](#struct_orgy_fraction_structure)` `[`modulus_fractions`](#fraction__math_8h_1a8b3e9f3e279ccb842a61ae8490c96959)`(`[`Fraction`](#struct_orgy_fraction_structure)` a,`[`Fraction`](#struct_orgy_fraction_structure)` b)`            | 
`public `[`Fraction`](#struct_orgy_fraction_structure)` `[`factorial_fraction`](#fraction__math_8h_1a5a68b5e9f579eaf0e7ccc499fd55ab09)`(`[`Fraction`](#struct_orgy_fraction_structure)` a)`            | 
`public int `[`compare_fractions`](#fraction__math_8h_1a50c53ea17596e7cf28eb58aadd7042d2)`(`[`Fraction`](#struct_orgy_fraction_structure)` a,`[`Fraction`](#struct_orgy_fraction_structure)` b)`            | 
`public `[`Fraction`](#struct_orgy_fraction_structure)` `[`pow_fractions`](#fraction__math_8h_1afa5a6802e6d6acfa2ac36cabce0574a1)`(`[`Fraction`](#struct_orgy_fraction_structure)` a,`[`Fraction`](#struct_orgy_fraction_structure)` b)`            | 
`struct `[`Link`](#struct_link) | 
`struct `[`OrgyChainStructure`](#struct_orgy_chain_structure) | 
`struct `[`OrgyFractionStructure`](#struct_orgy_fraction_structure) | 

## Members

#### `public void `[`init_chain`](#chain_8h_1ac96eb7de4c8b1a7e3570d9200ef2cc8f)`(`[`Chain`](#struct_orgy_chain_structure)` * chain)` 

Construct chain

Set defaults for chain: length to 0 and start to NULL

#### Parameters
* `chain` The chain being constructed

#### `public void `[`clear_chain`](#chain_8h_1aa4212f13a8d699b80b5c8fe4a5fab60b)`(`[`Chain`](#struct_orgy_chain_structure)` * chain)` 

Clear chain

Free all links in chain and set start to NULL

#### Parameters
* `chain` The chain being cleared

#### `public void `[`append_cstr_to_chain`](#chain_8h_1ad442feef450b8b012044dfd726af81a8)`(`[`Chain`](#struct_orgy_chain_structure)` * chain,const char * text)` 

#### `public void `[`append_flink_to_chain`](#chain_8h_1a2ae440a996132423425f5721b5c14d1b)`(`[`Chain`](#struct_orgy_chain_structure)` * chain,`[`Fraction`](#struct_orgy_fraction_structure)` fraction)` 

#### `public void `[`append_fraction_to_chain`](#chain_8h_1a116c3ec771d4a979a77eded5fdfc05a5)`(`[`Chain`](#struct_orgy_chain_structure)` * chain,`[`Fraction`](#struct_orgy_fraction_structure)` fraction)` 

#### `public void `[`append_chain_to_chain`](#chain_8h_1a902710243ebcd47c428a1dd41029ec2a)`(`[`Chain`](#struct_orgy_chain_structure)` * chain1,`[`Chain`](#struct_orgy_chain_structure)` chain2)` 

#### `public void `[`append_stream_to_chain`](#chain_8h_1a05e36086654b1484594e617f0abf364b)`(`[`Chain`](#struct_orgy_chain_structure)` * chain,FILE * stream)` 

#### `public void `[`chain_to_stream`](#chain_8h_1aa3115ee4f4c5671ac35c33102fd3e2d0)`(`[`Chain`](#struct_orgy_chain_structure)` chain,FILE * stream)` 

#### `public int `[`chain_to_cstr`](#chain_8h_1a784425b6bbc1c074e52e109871b526c0)`(`[`Chain`](#struct_orgy_chain_structure)` chain,char * buffer)` 

#### `public void `[`write_chain_to_file`](#chain_8h_1a897accbfb97acae9ff091b3dc13921c2)`(`[`Chain`](#struct_orgy_chain_structure)` chain,`[`Chain`](#struct_orgy_chain_structure)` filename)` 

#### `public void `[`read_file_to_chain`](#chain_8h_1a008ca35b36cfa01cebd59a6dddd79671)`(`[`Chain`](#struct_orgy_chain_structure)` * chain,`[`Chain`](#struct_orgy_chain_structure)` filename)` 

#### `public int `[`compare_chains`](#chain_8h_1aebea70af9ccbc3d25da67b8f836dba3d)`(`[`Chain`](#struct_orgy_chain_structure)` a,`[`Chain`](#struct_orgy_chain_structure)` b)` 

#### `public `[`Fraction`](#struct_orgy_fraction_structure)` `[`chain_to_fraction`](#chain_8h_1ae351d3cf295fd95456e64cb1bb9216da)`(`[`Chain`](#struct_orgy_chain_structure)` chain)` 

#### `public void `[`runtime_error`](#error_8h_1aa4581c050961a458136ec8bdd556d5b5)`(const char * msg,...)` 

Show error message and exit

Shows an error in the style of fprintf in red text, then exit with EXIT_FAILURE

#### Parameters
* `msg` The fprintf-style format string 

* `...` Any values referenced by the format string

#### `public `[`Fraction`](#struct_orgy_fraction_structure)` `[`construct_fraction`](#fraction_8h_1affd36cedc3799420c2d6ddfbdbd81ddf)`(FractionInt num,FractionInt den)` 

#### `public `[`Fraction`](#struct_orgy_fraction_structure)` `[`random_fraction`](#fraction_8h_1aff0108be8808ee831aaac374030930b4)`()` 

#### `public `[`Fraction`](#struct_orgy_fraction_structure)` `[`cryptorandom_fraction`](#fraction_8h_1a78d8f5be26e020fd33f5928b2aaf36b1)`()` 

#### `public `[`Fraction`](#struct_orgy_fraction_structure)` `[`time_fraction`](#fraction_8h_1a1287cf8ca974a6713dd6af32e2016524)`()` 

#### `public void `[`reduce_fraction`](#fraction__math_8h_1a945e863cbdcd274aef0eefb079d4b4d1)`(`[`Fraction`](#struct_orgy_fraction_structure)` * a)` 

#### `public `[`Fraction`](#struct_orgy_fraction_structure)` `[`add_fractions`](#fraction__math_8h_1a61a421cc3f02c994922da7b24aa4c4e1)`(`[`Fraction`](#struct_orgy_fraction_structure)` a,`[`Fraction`](#struct_orgy_fraction_structure)` b)` 

#### `public `[`Fraction`](#struct_orgy_fraction_structure)` `[`subtract_fractions`](#fraction__math_8h_1aba98b22dcee1e4eb95a7ac2fe9281e8d)`(`[`Fraction`](#struct_orgy_fraction_structure)` a,`[`Fraction`](#struct_orgy_fraction_structure)` b)` 

#### `public `[`Fraction`](#struct_orgy_fraction_structure)` `[`multiply_fractions`](#fraction__math_8h_1a4b4e5ede06559519a9a6894aeef10526)`(`[`Fraction`](#struct_orgy_fraction_structure)` a,`[`Fraction`](#struct_orgy_fraction_structure)` b)` 

#### `public `[`Fraction`](#struct_orgy_fraction_structure)` `[`divide_fractions`](#fraction__math_8h_1a94da26ba38d24c1688e08a9d8d7ae6c8)`(`[`Fraction`](#struct_orgy_fraction_structure)` a,`[`Fraction`](#struct_orgy_fraction_structure)` b)` 

#### `public `[`Fraction`](#struct_orgy_fraction_structure)` `[`modulus_fractions`](#fraction__math_8h_1a8b3e9f3e279ccb842a61ae8490c96959)`(`[`Fraction`](#struct_orgy_fraction_structure)` a,`[`Fraction`](#struct_orgy_fraction_structure)` b)` 

#### `public `[`Fraction`](#struct_orgy_fraction_structure)` `[`factorial_fraction`](#fraction__math_8h_1a5a68b5e9f579eaf0e7ccc499fd55ab09)`(`[`Fraction`](#struct_orgy_fraction_structure)` a)` 

#### `public int `[`compare_fractions`](#fraction__math_8h_1a50c53ea17596e7cf28eb58aadd7042d2)`(`[`Fraction`](#struct_orgy_fraction_structure)` a,`[`Fraction`](#struct_orgy_fraction_structure)` b)` 

#### `public `[`Fraction`](#struct_orgy_fraction_structure)` `[`pow_fractions`](#fraction__math_8h_1afa5a6802e6d6acfa2ac36cabce0574a1)`(`[`Fraction`](#struct_orgy_fraction_structure)` a,`[`Fraction`](#struct_orgy_fraction_structure)` b)` 

# struct `Link` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public `[`Fraction`](#struct_orgy_fraction_structure)` `[`value`](#struct_link_1a398f21bd9c8db3bf5e788b0495bc623d) | 
`public struct `[`Link`](#struct_link)` * `[`prev`](#struct_link_1af1e5687bdfac2994b98c23f359f4e0fd) | 
`public struct `[`Link`](#struct_link)` * `[`next`](#struct_link_1a4c0511c20c869c43fda58d1eeeed7e73) | 

## Members

#### `public `[`Fraction`](#struct_orgy_fraction_structure)` `[`value`](#struct_link_1a398f21bd9c8db3bf5e788b0495bc623d) 

#### `public struct `[`Link`](#struct_link)` * `[`prev`](#struct_link_1af1e5687bdfac2994b98c23f359f4e0fd) 

#### `public struct `[`Link`](#struct_link)` * `[`next`](#struct_link_1a4c0511c20c869c43fda58d1eeeed7e73) 

# struct `OrgyChainStructure` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public ChainLengthInt `[`length`](#struct_orgy_chain_structure_1aab51d8c9236300fa26ebafc6ef0d379c) | 
`public `[`Link`](#struct_link)` * `[`start`](#struct_orgy_chain_structure_1ae460f166a4376743febc0fdda9c4e120) | 
`public `[`Link`](#struct_link)` * `[`end`](#struct_orgy_chain_structure_1ad5738210a8e11389bfa78940cab43a41) | 

## Members

#### `public ChainLengthInt `[`length`](#struct_orgy_chain_structure_1aab51d8c9236300fa26ebafc6ef0d379c) 

#### `public `[`Link`](#struct_link)` * `[`start`](#struct_orgy_chain_structure_1ae460f166a4376743febc0fdda9c4e120) 

#### `public `[`Link`](#struct_link)` * `[`end`](#struct_orgy_chain_structure_1ad5738210a8e11389bfa78940cab43a41) 

# struct `OrgyFractionStructure` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public FractionInt `[`num`](#struct_orgy_fraction_structure_1af498157efbbc6c7c35e06669ee11cb48) | 
`public FractionInt `[`den`](#struct_orgy_fraction_structure_1a63e7e67b0b7d2d17e81df7027ea7ebe7) | 

## Members

#### `public FractionInt `[`num`](#struct_orgy_fraction_structure_1af498157efbbc6c7c35e06669ee11cb48) 

#### `public FractionInt `[`den`](#struct_orgy_fraction_structure_1a63e7e67b0b7d2d17e81df7027ea7ebe7) 

Generated by [Moxygen](https://sourcey.com/moxygen)