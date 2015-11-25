#import everything from matplotlib (numpy is accessible via 'np' alias)
from pylab import *

# Create a new figure of size 8x6 points, using 80 dots per inch
figure(figsize=(8,6), dpi=80)

# Create a new subplot from a grid of 1x1
ax = subplot(1,1,1)

#X = [10,20,40,80,160,320,640,1280,2560,5120,10240]
X = [100,1000,5000,10000]
#C = [2.6211,3.105,3.5564,4.1597,4.5139,4.9515,5.5412,6.0272,6.5374,7.0474,7.5223]
C = [4.35,6.987,8.787,9.965]
#LOGX = [3.32,4.32,5.32,6.32,7.32,8.32,9.32,10.32,11.32,12.32,13.32]
LOGX = [6.64,9.96,13.28]

# Plot cosine using blue color with a continuous line of width 1 (pixels)
plot(X, C, color="blue", linewidth=2.0, linestyle="--", marker='o')
#plot(LOGX, LOGX, color="blue", linewidth=1.0, linestyle="--")

# Plot sine using green color with a continuous line of width 1 (pixels)
# plot(X, S, color="green", linewidth=1.0, linestyle="-")

# Set x limits
xlim(0,10050)

# Set x ticks
#xticks([0,3.32,5.32,7.32,9.32,11.32,13.32],
#       [r'$1$', r'$10$', r'$40$', r'$160$', r'$640$', r'$2560$', r'$10240$'])
xticks([1,100,1000,5000,10000],
       [r'$1$', r'$100$', r'$1000$', r'$5000$', r'$10000$'])


#set x label
ax.set_xlabel('Number of nodes')

# Set y limits
ylim(0,50)

# Set y ticks
yticks([0,5,10,15,20,25,30,35,40,45,50],
       [r'$0$', r'$5$', r'$15$', r'$20$', r'$25$', r'$30$', r'$35$',r'$40$',r'$45$',r'$50$'])

#set y label
ax.set_ylabel('Occupancy')

# Save figure using 72 dots per inch
# savefig("exercice_2.png",dpi=72)

# Show result on screen
show()
