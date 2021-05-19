Analysing flat OpenData ntuples 

Ntuple source: https://opendata.cern.ch/record/15006

Use like:

   1. compile:
```

mkdir run && mkdir obj
# or whichever method you use to set up ROOT
lsetup ROOT 

make

```


   1. connect your branches and insert your code in:
```
CNtupAnaSkeleton/CNtupAnaSkeleton.h
CNtupAnaSkeleton/CNtupAnaSkeleton.cxx
```

   1. run like eg:
```
./run/RunNtupAna -i GamGam/MC/mc_343981.ggH125_gamgam.GamGam.root -t mini -o YourOutputFile.csv
```
```
./run/RunNtupAna -h # gives help
```
