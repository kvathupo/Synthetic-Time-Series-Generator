# Synthetic Dataset Generation
## Training
The program for generating the training data is found in `./main/gen-train.cpp`. 
Note that the parameters in `./include/utils.h` must be altered to the following
specifications.

All datasets are generated with 
1,000 time-steps and 
25 features. All processes
are generated with Boost's multiprecision arithmetic library to 50 decimal digits of 
precision (floating point). They are written to the CSVs with 25 decimal digits of 
precision.

All values are normalized according to:
* `./Norm-1/` - All values normalized to [-1, 1] 

### Autoregressive Stationary
In the following datasets, the target signal is a single salient process, which is 
stationary:

<p align="center">
    <img src="https://latex.codecogs.com/gif.latex?X_t%20%3D%200.2X_%7Bt-3%7D%20&plus;%200.5X_%7Bt-20%7D%20&plus;%20%5Cvarepsilon_t" />
</p>

In the CSVs, the 11th column is the target delayed by a single time-step.
It is seeded with a vector whose values are uniformly
chosen from [-1, 1). Thus, the saliency map should indicate the 50th feature and the time-delays
of 2 and 19 as most salient.

The resultant sequence is normalized to [-1, 1].

* `./Datasets/ARStat-0/` - All other time-series are zero
* `./Datasets/ARStat-1/` - All other time-series are strictly stationary
Gaussian white noise 
![equation](https://latex.codecogs.com/gif.latex?%5Cmathcal%7BN%7D%280%2C1%29)
* `./Datasets/ARStat-2/` - All other time-series are strictly stationary 
Gaussian white noise 
![equation](https://latex.codecogs.com/gif.latex?%5Cmathcal%7BN%7D%28%5Cmu%2C%20%5Csigma%5E2%29)
where the mean and standard deviation are uniformly sampled from \[-10, 10) and \[0.1, 5) respectively.
* `./Datasets/ARStat-3/` - All other time-series are unrelated, stationary AR processes
of the form ![equation](https://latex.codecogs.com/gif.latex?X_t%20%3D%20a%20&plus;%20b%20X_%7Bt-1%7D%20&plus;%20%5Cepsilon_t)
where `a` and `b` are uniformly sampled from [0, 1) and (-1, 1) respectively. To account
for the delay, the processes are seeded with a vector whose values are uniformly chosen 
from [-1, 1).
* `./Datasets/ARStat-4/` - All other time-series are unrelated, non-stationary AR processes.
To account for delays, the processes are seeded with a vector whose values are uniformly chosen 
from [-1, 1). These sequences are normalized to the range [-1, 1].

### Autoregressive Non-stationary, Non-linear (version 1)

In the following datasets, the target signal is a single salient process, which is
non-stationary with endogenous factors:

<p align="center">
    <img src="https://latex.codecogs.com/gif.latex?X_t%20%3D%200.4%28X_%7Bt-1%7D%29%5E3%20-%200.1%28X_%7Bt-3%7D%29%5E2%20&plus;%20%5Cvarepsilon_t" />
</p>

In the CSVs, the 50th feature is the target delayed by a single time-step.
It is seeded with a vector whose values are uniformly
chosen from \[-1, 1). Thus, the saliency map should indicate the 50th feature and the time-delays
of 2 and 19 as most salient.

The resultant sequence is normalized to [-1, 1].

* `./Datasets/ARNStat-0/` - All other time-series are zero
* `./Datasets/ARNStat-1/` - All other time-series are strictly stationary
Gaussian white noise 
![equation](https://latex.codecogs.com/gif.latex?%5Cmathcal%7BN%7D%280%2C1%29)
* `./Datasets/ARNStat-2/` - All other time-series are strictly stationary 
Gaussian white noise 
![equation](https://latex.codecogs.com/gif.latex?%5Cmathcal%7BN%7D%28%5Cmu%2C%20%5Csigma%5E2%29)
where the mean and standard deviation are uniformly sampled from \[-10, 10) and \[0.1, 5) respectively.
* `./Datasets/ARNStat-3/` - All other time-series are unrelated, stationary AR processes
of the form ![equation](https://latex.codecogs.com/gif.latex?X_t%20%3D%20a%20&plus;%20b%20X_%7Bt-1%7D%20&plus;%20%5Cepsilon_t)
where `a` and `b` are uniformly sampled from [0, 1) and (-1, 1) respectively. To account
for the delay, the processes are seeded with a vector whose values are uniformly chosen 
from [-1 ,1).
* `./Datasets/ARNStat-4/` - All other time-series are unrelated, non-stationary AR processes.
To account for delays, the processes are seeded with a vector whose values are uniformly chosen 
from [-1, 1). These sequences are normalized to the range [-1, 1].

### Autoregressive Non-stationary, Non-linear (version 2)

In the following datasets, the target signal is a single salient process, which is
non-stationary with endogenous factors:

<p align="center">
    <img src="https://latex.codecogs.com/gif.latex?X_t%20%3D%200.4%28X_%7Bt-1%7D%29%5E%7B0.5%7D%20-%200.1%28X_%7Bt-3%7D%29%5E7%20&plus;%20%5Cvarepsilon_t" />
</p>

In the CSVs, the 50th feature is the target delayed by a single time-step.
It is seeded with a vector whose values are uniformly
chosen from \[-1, 1). Thus, the saliency map should indicate the 50th feature and the time-delays
of 2 and 19 as most salient.

The resultant sequence is normalized to [-1, 1].

* `./Datasets/ARNStat-0/` - All other time-series are zero
* `./Datasets/ARNStat-1/` - All other time-series are strictly stationary
Gaussian white noise 
![equation](https://latex.codecogs.com/gif.latex?%5Cmathcal%7BN%7D%280%2C1%29)
* `./Datasets/ARNStat-2/` - All other time-series are strictly stationary 
Gaussian white noise 
![equation](https://latex.codecogs.com/gif.latex?%5Cmathcal%7BN%7D%28%5Cmu%2C%20%5Csigma%5E2%29)
where the mean and standard deviation are uniformly sampled from \[-10, 10) and \[0.1, 5) respectively.
* `./Datasets/ARNStat-3/` - All other time-series are unrelated, stationary AR processes
of the form ![equation](https://latex.codecogs.com/gif.latex?X_t%20%3D%20a%20&plus;%20b%20X_%7Bt-1%7D%20&plus;%20%5Cepsilon_t)
where `a` and `b` are uniformly sampled from [0, 1) and (-1, 1) respectively. To account
for the delay, the processes are seeded with a vector whose values are uniformly chosen 
from [-1 ,1).
* `./Datasets/ARNStat-4/` - All other time-series are unrelated, non-stationary AR processes.
To account for delays, the processes are seeded with a vector whose values are uniformly chosen 
from [-1, 1). These sequences are normalized to the range [-1, 1].

### Autoregressive Non-stationary

In the following datasets, the target signal is a single salient process, which is
non-stationary with endogenous factors:

<p align="center">
    <img src="https://latex.codecogs.com/gif.latex?X_t%20%3D%200.75X_%7Bt-3%7D%20-%200.9X_%7Bt-20%7D%20&plus;%20%5Cvarepsilon_t" />
</p>

In the CSVs, the 50th feature is the target delayed by a single time-step.
It is seeded with a vector whose values are uniformly
chosen from \[-1, 1). Thus, the saliency map should indicate the 50th feature and the time-delays
of 2 and 19 as most salient.

The resultant sequence is normalized to [-1, 1].

* `./Datasets/ARNStat-0/` - All other time-series are zero
* `./Datasets/ARNStat-1/` - All other time-series are strictly stationary
Gaussian white noise 
![equation](https://latex.codecogs.com/gif.latex?%5Cmathcal%7BN%7D%280%2C1%29)
* `./Datasets/ARNStat-2/` - All other time-series are strictly stationary 
Gaussian white noise 
![equation](https://latex.codecogs.com/gif.latex?%5Cmathcal%7BN%7D%28%5Cmu%2C%20%5Csigma%5E2%29)
where the mean and standard deviation are uniformly sampled from \[-10, 10) and \[0.1, 5) respectively.
* `./Datasets/ARNStat-3/` - All other time-series are unrelated, stationary AR processes
of the form ![equation](https://latex.codecogs.com/gif.latex?X_t%20%3D%20a%20&plus;%20b%20X_%7Bt-1%7D%20&plus;%20%5Cepsilon_t)
where `a` and `b` are uniformly sampled from [0, 1) and (-1, 1) respectively. To account
for the delay, the processes are seeded with a vector whose values are uniformly chosen 
from [-1 ,1).
* `./Datasets/ARNStat-4/` - All other time-series are unrelated, non-stationary AR processes.
To account for delays, the processes are seeded with a vector whose values are uniformly chosen 
from [-1, 1). These sequences are normalized to the range [-1, 1].


### Autoregressive-moving-average with Exogenous Inputs
Let us establish notation. Denote the features by `x` where the superscript 
corresponds to feature index and the subscript corresponds to time-delay.
Denote the target signal by `y`.

In the following datasets, the target signal is the following ARMAX(0,0,3) model:

<p align="center">
    <img src="https://latex.codecogs.com/gif.latex?Y_t%20%3D%200.1%20%5Ccdot%20X%5E%7B%285%29%7D_%7Bt-1%7D%20&plus;%200.25%20%5Ccdot%20X%5E%7B%2810%29%7D_%7Bt-3%7D%20&plus;%200.5%20%5Ccdot%20X%5E%7B%2820%29%7D_%7Bt-5%7D%20&plus;%20%5Cepsilon_t" />
</p>

The factors are non-stationary AR processes seeded with vector whose values are
uniformly chosen from [-1, 1).

The resultant sequence is normalized to [-1, 1].

* `./Datasets/ARMAX-0/` - All other time-series are zero
* `./Datasets/ARMAX-1/` - All other time-series are strictly stationary
Gaussian white noise 
![equation](https://latex.codecogs.com/gif.latex?%5Cmathcal%7BN%7D%280%2C1%29)
* `./Datasets/ARMAX-2/` - All other time-series are strictly stationary 
Gaussian white noise 
![equation](https://latex.codecogs.com/gif.latex?%5Cmathcal%7BN%7D%28%5Cmu%2C%20%5Csigma%5E2%29)
where the mean and standard deviation are uniformly sampled from \[-10, 10) and \[0.1, 5) respectively.
* `./Datasets/ARMAX-3/` - All other time-series are unrelated, stationary AR processes
of the form ![equation](https://latex.codecogs.com/gif.latex?X_t%20%3D%20a%20&plus;%20b%20X_%7Bt-1%7D%20&plus;%20%5Cepsilon_t)
where `a` and `b` are uniformly sampled from [0, 1) and [-1, 1) respectively. To account
for the delay, the processes are seeded with a vector whose values are uniformly chosen 
from [-1, 1).
* `./Datasets/ARMAX-4/` - All other time-series are unrelated, non-stationary AR processes.
To account for delays, the processes are seeded with a vector whose values are uniformly chosen 
from [-1, 1). These sequences are normalized to the range [-1, 1].

## Development 
Compile with 
```
g++ -Wall -std=c++17 -fsanitize=undefined,leak,address ./test/main.cpp ./lib/*.cpp -I ./include/
```
Requires Boost.
