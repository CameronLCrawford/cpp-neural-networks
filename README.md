# cpp-neural-networks
Simple showcase of neural networks which allows the creation and training of networks of arbitrary architecture.

# Matrices
The Matrix class is used largely in the neural networks and allows for the creation of matrices of any dimensions. The data for the matrix is passed in as a vector and the matrices only store floats. The data in the matrix can be accessed and modified and addition, subtraction, and multiplication (between two matrices) have all been overriden. There is also a function for pretty-printing the matrices in rows and columns and this overrides the << operator.

# Neural Networks
These are instantiated by passing in the number of layers and the size of each layer. Every layer of the network (bar the input layer) consists of nodes which each have a sigmoid activation function and no biases. The training can be performed in batches as the backpropagation algorithm only updates the stored cumulative delta for each weight until it is updated at the end of the batch.

# The example
To show off the capabilities of the neural networks, a simple architecture is created which trains on the famous "iris" dataset (https://archive.ics.uci.edu/ml/datasets/Iris) and delivers a very high accuracy within only 500 epochs. The data file is space delimited and read into two sets, the train and the test data. The model is then trained before being tested.
