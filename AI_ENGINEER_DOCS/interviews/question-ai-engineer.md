# AI Engineering - Comprehensive Interview Q&A Guide

This document contains a complete test exam analysis with fully improved and detailed technical answers for an AI/Data Engineering role. It tackles various domains from Machine Learning fundamentals and Deep Learning to MLOps, LLMs, and RAG pipelines.

---

## Question 1: Model Training Accuracies & Overfitting
**Scenario:** A model's training accuracy continuously increases from 0.60 to 0.96 over 9 epochs. However, validation accuracy peaks at 0.83 at epoch 6 and then drops to 0.70 by epoch 9.

*   **What is the most likely problem?**
    The model is experiencing **Overfitting**. After epoch 6, the model starts memorizing the noise in the training data rather than learning generalized patterns, causing the training accuracy to keep increasing while the validation accuracy degrades.
*   **Name two techniques to reduce this problem:**
    1.  **Early Stopping:** Halt the training process at the epoch where validation accuracy is highest (Epoch 6) to lock in the optimal weights before overfitting starts.
    2.  **Regularization & Dropout / Data Augmentation:** Apply L1/L2 weight penalties or add Dropout layers to penalize overly complex models. Alternatively, use data augmentation to artificially increase the training set size, preventing the model from memorizing specific samples.
*   **What is the best epoch for deployment and why?**
    **Epoch 6.** This is the point where the validation accuracy is maximized (0.83). It represents the optimal balance in the Bias-Variance tradeoff before variance explodes.
*   **If validation accuracy kept increasing together with training accuracy, what would that indicate?**
    It would indicate that the model is still learning healthy, generalized patterns and has not yet converged. You should continue training for more epochs until validation accuracy plateaus or starts dropping.

---

## Question 2: Handling Imbalanced Datasets
**Scenario:** You are solving a binary classification problem: 90% negative, 10% positive.

*   **Describe two precise training techniques:**
    1.  **Class Weighting (Cost-Sensitive Learning):** Assign a higher penalty (weight) in the loss function for misclassifying the minority class. 
    2.  **SMOTE (Synthetic Minority Over-sampling Technique):** Synthetically generate new examples of the minority class by interpolating between existing minority data points in the feature space.
*   **Explain mathematically or intuitively why it works:**
    *   *Class weights:* If the minority class is weighted by 9x, the model's gradient update will be pushed 9 times harder when it makes an error on a positive sample, forcing the decision boundary to accommodate the minority class.
    *   *SMOTE:* Instead of duplicating exact copies of data (which leads to overfitting), SMOTE creates realistic variance in the minority class, expanding its decision region.
*   **Would you apply it at test time?**
    **No.** Data balancing techniques (like SMOTE) and loss function tweaks are strictly for adjusting the model's learned weights during *training*. At test time, the model must evaluate real-world, untouched, imbalanced data distributions.

---

## Question 3: Evaluation Metrics for Fraud
**Scenario:** AI for fraud detection. Missing fraud costs $50,000. False alarms cost $500.

*   **Most appropriate evaluation metric:** **Recall**
*   **Explain why:** 
    Recall measures the proportion of actual positive cases (frauds) that were correctly identified. Since the cost of a False Negative (missing a fraud, $50k) is 100 times higher than a False Positive (false alarm, $500), we must prioritize minimizing False Negatives. Optimizing for high Recall ensures the system catches as many frauds as possible, even at the cost of investigating a few more false alarms.

---

## Question 4: The 1x1 Convolution
*   **Primary computational benefit:** **Dimensionality Reduction (Channel compression).** It allows you to decrease the number of channels (feature maps) without altering the spatial dimensions (height and width).
*   **Example use case:** The **Inception module (GoogLeNet)** or **ResNet bottleneck blocks**.
*   **Computation trade-off:** By placing a 1x1 convolution before expensive 3x3 or 5x5 convolutions, you drastically reduce the input depth. This massively lowers the total number of parameters and floating-point operations (FLOPs), allowing you to build much deeper networks without exceeding memory and compute limits.

---

## Question 5: BERT vs. Generative LLM Embeddings
*   **Architecture:**
    *   **BERT:** Encoder-only Transformer. Uses bidirectional self-attention to read the entire text sequence simultaneously from left-to-right and right-to-left.
    *   **Gen LLM (e.g., GPT):** Decoder-only Transformer. Uses masked (causal) self-attention, reading text strictly from left to right.
*   **Model Size:**
    *   **BERT:** Relatively small (e.g., BERT-Base is ~110M, Large is ~340M parameters). Very fast and cheap to fine-tune.
    *   **Gen LLM:** Massive (typically ranging from 7B up to 175B+ parameters). High memory, slow inference, and costly.
*   **Training Objective:**
    *   **BERT:** Trained using Masked Language Modeling (MLM)—predicting randomly hidden words in a sentence, optimizing for deep contextual understanding of complete sentences.
    *   **Gen LLM:** Trained using Causal Language Modeling (Next Token Prediction)—optimizing for text generation and reasoning sequential outputs.

---

## Question 6: Mitigating LLM Hallucinations in Production
**Scenario:** Live Vietnamese LLM has polite but subtly wrong facts. No retraining allowed.

*   **High-level idea:** Implement a **RAG (Retrieval-Augmented Generation)** integration combined with a Post-processing Validation guardrail.
*   **How it prevents hallucinations:** Before sending the prompt to the LLM, retrieve factual context from a vetted internal knowledge base. Augment the prompt to force the LLM to answer *only* based on the retrieved context.
*   **Limitation or risk:** Retrieval algorithms might fail to pull the correct document, or the added lookup steps will increase latency and token costs.
*   **Metric to track:** **Hallucination Rate** (measured via regular sampling and human-in-the-loop auditing, or using an auxiliary small NLI-based AI model to measure entailment between the generated answer and the source documents).

---

## Question 7: RAG Pipeline Optimization
**Scenario:** Current Pipeline: User Msg -> LLM rewrite -> Retrieve -> *LLM re-rank* -> LLM final answer.
*   **Issues:** The biggest killer here is **Latency and Cost**. Making three separate calls to a massive LLM (Rewrite, Re-rank sequence, and Generate) for a chatbot meant for instant replies is unacceptably slow. Re-ranking chunks purely with an LLM in sequence is O(N) calls per chunk, which is extremely inefficient.
*   **How to improve it:**
    Replace the LLM Re-ranker with a fast, specialized **Cross-Encoder Model** (e.g., MiniLM or BGE-Reranker). These models run locally, are highly optimized, and compare queries to chunks in milliseconds. Additionally, you can occasionally bypass the LLM rewrite step if the original user prompt is long and detailed enough, saving an entire LLM roundtrip.

---

## Question 8: RAG Chunking Challenges (Markdown)
**Scenario:** 300 Markdown docs (no headings). 1: Partial lists returned. 2: Code blocks distorted. 3: Content at end of docs ignored.
*   **Solution Strategy:**
    1.  **For Lists and Code Blocks (Structural Chunking):** Standard fixed-size token chunkers blindly slice through lists and code wrappers (` ``` `). Replace the standard chunker with a **Markdown-aware/Semantic Chunker**. This parser looks for code block boundaries and newline list identifiers, guaranteeing that code blocks and continuous lists remain entirely intact within a single chunk payload.
    2.  **For Broad Summaries / End of Document content (Parent-Child / Hierarchical Retrieval):** Use a smaller chunk size with high overlap for the embedding/retrieval vector space to ensure high accuracy. However, when a chunk is matched, return its entire **Parent Document** (or a massive window around it) to the final generative LLM. This provides the LLM with the full policy list or the end-of-document conclusions that surrounding chunks contained.

---

## Question 9: Decision Trees, Random Forests, & Boosting
*   **Decision Tree:** 
    *   *Advantage:* Easy to interpret, robust to raw data (no scaling needed). 
    *   *Limitation:* Extremely prone to Overfitting (High Variance) because they build deep branches that completely memorize the training data.
*   **Random Forest (Bagging):** 
    *   How it fixes it: It trains multiple deep, overfitted trees independently on random subsets of data and features. By averaging these uncorrelated trees, it dramatically reduces **Variance** without increasing Bias, creating a robust model immune to the overfitting trap.
*   **Boosting (AdaBoost / Gradient Boosting):**
    *   How it fixes it: Boosting builds very shallow, weak trees (low variance, high bias) sequentially. Every new tree specifically targets the errors (residuals) made by the previous trees. It directly reduces **Bias** while slowly building a strong, combined predictive engine.

---

## Question 10: RNNs and the Vanishing Gradient
*   **Why RNNs are suitable:** Unlike feed-forward networks, RNNs possess a "hidden state" that persists across time steps. This allows them to process sequential data of arbitrary length and maintain a memory of previous inputs to influence current outputs.
*   **Vanishing Gradient Cause:** During training, errors are propagated backward through time (BPTT). This requires continuously multiplying the same hidden transition weights. If these weights are even slightly less than 1, multiplying them repeatedly across a long sequence causes the gradient to shrink exponentially to near zero. Consequently, early layers never update their weights, meaning the model "forgets" long-term dependencies.
*   **How LSTM addresses it:** LSTMs replace the standard RNN node with a Memory Cell governed by three gates (Forget, Input, Output). Crucially, the cell state allows gradients to flow directly through time via **addition** rather than pure multiplication, bypassing the exponential decay and allowing the network to retain information over hundreds of timesteps.
