# RNN & LSTM

## RNN

**Recurrent Neural Network (RNN)** is a class of **artificial neural networks** where **connections between nodes form a directed graph along a temporal sequence**. This allows the network to exhibit **temporal dynamic behavior**, making it suitable for processing sequential data such as text, speech, and time series.

### Base concept

**The core idea of RNN is to maintain a hidden state that captures information from previous time steps and uses it to process the current time step.**

**Example**

**Imagine you are reading a book. To understand the current sentence, you need to remember what happened in the previous sentences. RNNs work similarly by maintaining a hidden state that acts as a "memory" of past information.**

### Problem

*   **Vanishing Gradient Problem:** As the sequence length increases, the gradients propagated back through time become progressively smaller, making it difficult for the network to learn long-term dependencies.
*   **Exploding Gradient Problem:** As the sequence length increases, the gradients propagated back through time become progressively larger, making the network unstable.
*   **Output:** In 1 block of time, RNN can only output 1 value. In that case, the output summary of the whole sequence is the last output value. This is not good for tasks that require the output to be the whole sequence. For example, if we want to summarize a long text, the last output value is not enough to summarize the whole text.

## LSTM

**LSTM** is a type of RNN that is designed to overcome **the limitations of RNNs**. It's 

### Base concept

**The core idea of LSTM is to maintain a cell state that acts as a "conveyor belt" for information, allowing it to flow through the network largely unchanged.**

**Example**

The information flow in LSTM is as follows:

**Input gate:** **Decides which information from the current input** should be added to the cell state. It is a sigmoid layer that outputs a value between 0 and 1. If the value is 1, the information is added to the cell state. If the value is 0, the information is not added to the cell state.

**Forget gate:** **Decides which information from the previous cell state** should be removed. It is a sigmoid layer that outputs a value between 0 and 1. If the value is 1, the information is not removed. If the value is 0, the information is removed.

**Output gate:** **Decides which information from the current cell state** should be outputted. It is a sigmoid layer that outputs a value between 0 and 1. If the value is 1, the information is outputted. If the value is 0, the information is not outputted.

**Cell state:** The cell state is the "conveyor belt" that carries information through the network. The information flows through the cell state largely unchanged, allowing the network to learn long-term dependencies. 

**Summary** The LSTM has the concept of "forget gate" which allows it to forget irrelevant information. This is a key difference between LSTM and RNN. if we are processing a text, the LSTM can forget the irrelevant information and remember the relevant information. For example, if we are processing a text about a person, the LSTM can forget the irrelevant information and remember the relevant information.

