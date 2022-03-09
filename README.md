# Synthetic Time-Series Generator
## What?
`./gen-data/`:

C++ code that procedurally generates time-series data according to a specified
stochastic process. Data is output as CSVs. The following processes are supported:

* Autoregressive (AR) processes
* Autoregressive processes with polynomial dependence on lagged values
* Autoregressive–moving-average (ARMA) processes
* Autoregressive–moving-average processes with exogenous inputs (ARMAX)
 
`./aug-data/`:

C++ code that augments existing time-series with additive noise sampled from 
a Gaussian white noise process. Data is handled as CSVs for both input and output.
## Why?
This code was originally written when I was doing research at UMD. Although this
repo primarily exists as a record of my work, I'll likely edit the READMEs for
legibility soon. After all, what good is showcasing code that 
can't be understood?
