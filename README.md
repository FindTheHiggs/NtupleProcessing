Analysing flat OpenData ntuples 

Ntuple source: https://opendata.cern.ch/record/15006

Use like:

   1. compile:
```
# before 1st compilation, make dirs for object and binary (executable)
mkdir obj && mkdir bin
# or whichever method you use to set up ROOT
lsetup ROOT 

make

```


   1. connect your branches and insert your code in:
```
NtupAnaSkeleton/NtupAnaSkeleton.h
NtupAnaSkeleton/NtupAnaSkeleton.cxx
```

   1. run like eg:
```
# MC:
./bin/RunNtupAna -i GamGam/MC/mc_343981.ggH125_gamgam.GamGam.root -t mini -o YourOutputFile.csv

# data:
./bin/RunNtupAna -l data_list.txt -t mini -o ti_data.csv

```
```
./bin/RunNtupAna -h # gives help
```


   1. Technical details:
   The following is steered from within analyse() function in NtupAnaSkeleton.cxx: 
    ..1. TI/NTNT flags: The BDT is trained for the signal hypothesis: ggH125 and background hypothesis: non-tight or non-isolated (NTNI) data. The prediction is then applied to tight and isolated (TI) data, as in actual ATLAS analysis. 
    ..2. event pre-selection, requiring eg myy cuts. 
