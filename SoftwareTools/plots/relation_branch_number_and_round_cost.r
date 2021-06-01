# Written by Denise Verbakel
# I used RStudio to run this program and get the corresponding output file (relation_branch_number_and_round_cost.png) 

#bbn = bit branch number
#noopb = number of operations per bit

# Assign the corresponding values to the vectors bbn and noopb
bbn <- c(6,5,2,2,2,4)
noopb <- c(3,2.25,0.75,0.75,0,2)

# Compute the averages and estimated values
bbn_bar = sum(bbn)/length(bbn)
noopb_bar = sum(noopb)/length(noopb)
beta_hat = sum((bbn-bbn_bar)*(noopb-noopb_bar))/sum((bbn-bbn_bar)^2)
alpha_hat = noopb_bar - beta_hat * bbn_bar

# Make a scatterplot of the data points and draw the estimated average with a red line
plot(bbn,noopb,
     xlab="Bit Branch Number",
     ylab="# Operations Per Bit",
     pch=16,
     cex.axis=1.5,
     cex.lab=1.5)
abline(alpha_hat,beta_hat,
       col='red',
       lwd=2)
