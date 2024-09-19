
// the term object is how you make a contract in yul
object "HorseStoreYul" {
    code{
        // Contract deployment........

        datacopy(0, dataoffset("runtime"), datasize("runtime"))
        return(0, datasize("runtime"))
    }
}