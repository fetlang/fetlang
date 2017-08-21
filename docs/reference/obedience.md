# Obedience
Operators for manipulating files
## Operators
### demand obedience of
Read a file to a chain, given a filename  

Grammar: have  
C Code:  

    /* chain/chain overload */
    read_file_to_chain(&LHO, RHO);  

### obey
Write a chain to file, given a filename  

Grammar: have  
C Code:  

    /* chain/chain overload */
    write_chain_to_file(LHO, RHO)  

### serve
Set LHO as a stream pointing to a file, given a filename  

Grammar: make  
C Code:  

    /* stream/chain overload */
    LHO = open_file_as_stream(RHO, "r+b")  

