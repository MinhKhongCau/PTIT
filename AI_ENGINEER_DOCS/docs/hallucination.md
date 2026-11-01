# Hallucination

**Hallucination** is a phenomenon in Large Language Models (LLMs) where the model generates text that is **factually incorrect, nonsensical, or not grounded in the input context**, yet presents it confidently as truth.

## Why do LLMs Hallucinate?

1.  **Training Data Limitations:**
    - **Incomplete Knowledge:** The model's training data has a cutoff date. It cannot know about events or facts that occurred after its training. When asked, it might invent plausible-sounding information.
    - **Biases & Errors:** If the training data contains misinformation or biases, the model may reproduce them.

2.  **Probabilistic Nature:**
    - LLMs are essentially sophisticated **next-token predictors**. They choose the most statistically probable word based on patterns learned during training. Sometimes, the most probable sequence of words does not align with factual reality.

3.  **Over-Optimization for Fluency:**
    - Models are trained to produce text that sounds human and coherent. This optimization goal can sometimes override factual accuracy, leading to fluent but fabricated responses.

4.  **Ambiguous or Leading Prompts:**
    - If a user's prompt contains false premises or is ambiguous, the model may accept those premises and generate a response based on them.

## Types of Hallucinations

- **Factual Hallucinations:** Stating incorrect facts (e.g., "The capital of Australia is Sydney").
- **Contextual Hallucinations:** Inventing details not present in the input context (e.g., adding characters or events to a story summary that weren't there).
- **Citation Hallucinations:** Citing non-existent sources or fabricating quotes.

## Mitigation Strategies

- **Retrieval-Augmented Generation (RAG):** Grounding the model's responses in external, verified knowledge bases.
- **Fact-Checking Layers:** Implementing post-processing steps to verify generated claims.
- **Improved Training Data:** Curating higher-quality, factually accurate training datasets.
- **Prompt Engineering:** Designing prompts that encourage the model to admit uncertainty or rely on provided context.
