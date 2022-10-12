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
