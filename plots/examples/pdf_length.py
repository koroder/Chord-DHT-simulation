#import everything from matplotlib (numpy is accessible via 'np' alias)
from pylab import *

# Create a new figure of size 8x6 points, using 80 dots per inch
figure(figsize=(8,6), dpi=80)

# Create a new subplot from a grid of 1x1
ax = subplot(1,1,1)

X = [1,2,3,4,5,6,7,8,9,10,11,12,13,14]
C = [0.0001,0.0013,0.0079,0.0356,0.0808,0.157,0.2175,0.2129,0.1611,0.084,0.0312,0.0094,0.0011,0.0001]

# Plot cosine using blue color with a continuous line of width 1 (pixels)
plot(X, C, color="red", linewidth=2.0, linestyle="-")

# Plot sine using green color with a continuous line of width 1 (pixels)
# plot(X, S, color="green", linewidth=1.0, linestyle="-")

# Set x limits
xlim(0,15)

# Set x ticks
xticks([0,2,4,6,8,10,12,14])

#set x label
ax.set_xlabel('Path Length')

# Set y limits
ylim(0,0.25)

# Set y ticks
yticks([0,0.05,0.10,0.15,0.20,0.25])

#set y label
ax.set_ylabel('PDF')

# Save figure using 72 dots per inch
# savefig("exercice_2.png",dpi=72)

# Show result on screen
show()
