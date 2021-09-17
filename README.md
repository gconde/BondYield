# BondYield
### Windows Build
---
To build on Windows install Qt at least version 5.10. The project files are Visual Studio 2017 which is the recommended version to use. Also install the Qt visual studio add-in which can be found on the Visual Studio Marketplace. Open the solution in Visual Studio and build the usual way.
### Linux Build
---
To build on Linux be sure to have installed the Qt5 development libraries for your distribution as well as developer tools such as compiler, build tools, etc. Then run the build.sh script which will create a makefile and execute the appropriate targets.

Alternatively a Dockerfile is included if you don't have and/or don't want to install all the dependencies. Example from the Dockerfile directory run:
```
sudo systemctl start docker.service
docker build -t bond_yield-app .
docker run --net=host --env="DISPLAY" --volume="$HOME/.Xauthority:/root/.Xauthority:rw" bond_yield-app
```
### Code Documentation
---
Doxygen documentation is available here: https://gconde.github.io/BondYield/
### Bond Yield Calculator Background
---
Fixed-income securities, such as a bond, are priced according to the cash flows that the holder will receive, and when they will receive them. Cash received sooner is worth more than cash received later, simply because the holder can reinvest the cash they receive now and realize a gain. If they have to wait for the cash to come in, the holder will not be able to reinvest it until later.

The gain that the holder can realize on a cash flow is based on the current interest rate. For the sake of simplicity, let’s say there is a cash flow CF, and that it’s reinvested at an annual rate of *r*. The cash that the holder will receive in N years is simply:

![CF_{1}=CF*(1+r)^{^{N}}](https://latex.codecogs.com/svg.latex?CF_%7B1%7D%3DCF*%281&plus;r%29%5E%7B%5E%7BN%7D%7D)

This is the standard and straightforward compound interest calculation.

With this in mind, we can actually discount a cash flow received in N years back to its present value, given a rate *r*. If we receive a cash flow CF1 in N years, we know that its present value CF is simply:

![CF=\frac{CF_{1}}{(1+r)^{N}}](https://latex.codecogs.com/svg.latex?CF%3D%5Cfrac%7BCF_%7B1%7D%7D%7B%281&plus;r%29%5E%7BN%7D%7D)

This equation is simply the first equation, but with both sides divided by ![{(1+r)^{N}}](https://latex.codecogs.com/svg.latex?%7B%281&plus;r%29%5E%7BN%7D%7D). When it’s written like this, the rate *r* is often referred to as the *discount* rate.

Now a bond is simply a set of cash flows. If a company issues an annual-pay, 5-year, $1000 bond with a 10% coupon, this means two things:
1. The company will receive some amount of money up front from the bondholder, when they purchase the security.
2. In exchange for that money, the company will make two sets of payments to the bondholder: first, the company will make a coupon payment of $100 (10% of $1000) each year for 5 years; second, at the end of the 5th year, the company will make a principal payment of $1000.

So how much money does the bondholder have to pay to receive those cash flows? Namely, how much is the “some amount of money” mentioned above? That can be determined by the discount technique described above, along with an assumed rate. Assuming a discount rate of 15%, the specific bond described above will have the sum of its discounted cash flows – their present values – as given by:

![\sum PV = \frac{100}{1.15^{1}}+\frac{100}{1.15^{2}}+\frac{100}{1.15^{3}}+\frac{100}{1.15^{4}}+\frac{100}{1.15^{5}}+\frac{1000}{1.15^{5}}=832.4](https://latex.codecogs.com/svg.latex?%5Csum%20PV%20%3D%20%5Cfrac%7B100%7D%7B1.15%5E%7B1%7D%7D&plus;%5Cfrac%7B100%7D%7B1.15%5E%7B2%7D%7D&plus;%5Cfrac%7B100%7D%7B1.15%5E%7B3%7D%7D&plus;%5Cfrac%7B100%7D%7B1.15%5E%7B4%7D%7D&plus;%5Cfrac%7B100%7D%7B1.15%5E%7B5%7D%7D&plus;%5Cfrac%7B1000%7D%7B1.15%5E%7B5%7D%7D%3D832.4)

The first 5 terms in the equation are simply the annual coupon payments, discounted to their present values (for example, the coupon payment that is coming 3 years from now has to be discounted by ![{1.15^{3}}](https://latex.codecogs.com/svg.latex?%7B1.15%5E%7B3%7D%7D), the one that is coming 4 years from now has to be discounted by ![{1.15^{4}}](https://latex.codecogs.com/svg.latex?%7B1.15%5E%7B4%7D%7D) , etc.). The last term is the principal payment, also discounted to its present value. The sum of all of those present values, $832.4, is *the price of the bond*. This is how much the bondholder will have to pay, up front, in order to receive those cash flows from the issuer.

Why is the price of the bond less than $1000? Well, in an environment where interest rates are 15%, receiving $100 annually on an investment of $1000 is not worthwhile to the holder. They could simply put their money in some other investment at 15%, and get $50 more a year. So the bond has to be offered at a discount; it has to be offered for less than $1000 in order to entice someone to buy it.

If the bond price is $832.4, that means that it will yield a return of 15% to the holder over the lifetime of the bond – and in fact the full name of that return is called yield to maturity (YTM). **Note that in this particular context, YTM is the same thing as the interest rate, and it’s the same thing as the discount rate. The terms yield, yield to maturity, discount rate, and interest rate can be used interchangeably. They all refer to the rate *r*.**

This bond pricing equation can be generalized. For a particular bond with a coupon payment of C, a time of N years, and a face amount of F, the price of the bond for a given rate *r* is:

![\mathit{Price}=\frac{C}{{(1+r)}^{1}}+\frac{C}{{(1+r)}^{2}}+\frac{C}{{(1+r)}^{3}}+\cdots +\frac{C}{{(1+r)}^{N}}+\frac{F}{{(1+r)}^{N}}](https://latex.codecogs.com/svg.latex?%5Cmathit%7BPrice%7D%3D%5Cfrac%7BC%7D%7B%7B%281&plus;r%29%7D%5E%7B1%7D%7D&plus;%5Cfrac%7BC%7D%7B%7B%281&plus;r%29%7D%5E%7B2%7D%7D&plus;%5Cfrac%7BC%7D%7B%7B%281&plus;r%29%7D%5E%7B3%7D%7D&plus;%5Ccdots%20&plus;%5Cfrac%7BC%7D%7B%7B%281&plus;r%29%7D%5E%7BN%7D%7D&plus;%5Cfrac%7BF%7D%7B%7B%281&plus;r%29%7D%5E%7BN%7D%7D)

### Implementation
---
A GUI is implemented with Qt for ease of use.

The math for the bond price is straightforward. The calculation for the rate requires a numerical approach. Two such approaches are implemented. There is an iterative method which arrives at a solution linearly and a superior yield algorithm which is discussed in detail here: [Superseding Newton with a Superior Yield Algorithm by Chris Deeley :: SSRN](https://papers.ssrn.com/sol3/papers.cfm?abstract_id=1253166) Either method can be used and the time to convergence is also reported to verify performance.
