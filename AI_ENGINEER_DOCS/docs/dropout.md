# Dropout in Neural Networks

**Dropout** is an incredibly powerful, computationally cheap, and widely used Regularization technique exclusively used in Deep Neural Networks to prevent **Overfitting**.

## The Principle
Dropout works by **randomly "dropping out" (deactivating) a subset of neurons** during the training phase. 

At every training batch (or step), each neuron in a layer is temporarily ignored (its output is set to 0) with a predefined probability `p` (often between 0.2 and 0.5).

### Why does this prevent Overfitting?
1.  **Prevents Co-adaptation:** In standard networks, specific neurons might develop codependencies on each other to fix mistakes. If one neuron dominates, the network relies on it too exclusively. Dropout breaks these dependencies, forcing the network to learn robust, generalized representations across all available neurons.
2.  **Ensemble Effect:** Because different combinations of neurons are active on every forward pass, training a neural network with dropout is mathematically similar to training thousands of slightly different sub-networks (an ensemble) and averaging their predictions. Ensembles systematically reduce variance.

---

## Training Phase vs. Inference (Evaluation) Phase

It is critical to understand that Dropout acts differently during training versus deployment:

1.  **During Training:** Neurons are actively randomly dropped with probability `p`. Only `(1 - p)` of the neurons are actively firing.
2.  **During Inference/Testing:** Dropout is completely turned off. **All neurons are active** to maximize the model's predictive power. 
    *   *Weight Scaling:* Because all neurons are now active, the total sum of activation values passing to the next layer will be unexpectedly large. To compensate, the network automatically scales down the weights by a factor of `(1 - p)` during test time (or scales them up during training, known as *Inverted Dropout*) so the expected value remains consistent.

## Implementation Example (PyTorch / Keras)
You typically apply dropout right after the activation function of dense/fully-connected layers:
`Linear/Dense -> ReLU -> Dropout(p=0.3) -> Linear/Dense`
