# RAG Pineline

**Retrieval-Augemented Generation (RAG)** is a technique that **combines** the power of **large language models (LLMs)** with **the ability** to retrieve **relevant information** from a **knowledge base**. It is a way to improve **the accuracy and relevance** of LLM outputs by providing them with additional context.

**Core concept** The core idea of RAG is to first retrieve relevant information from a knowledge base and then use that information to generate a response. This is in contrast to traditional LLMs that generate responses based on their training data alone.

1. Data Ingestion pineline(Indexing):

- **Document loading**: Load documents from various sources such as PDF, DOCX, TXT, etc.
- **Chunking**: **Split** the **document** into smaller **chunks**.
- **Embedding**: Convert **the chunks into vectors**.
- **Vector store**: Store the vectors in a **vector database**.

2. Retrieval pineline:

- **Query embedding**: Convert the query into a **vector**.
- **Similarity search**: Finding **most revelant chunks** from the vector store.
- **Augmented prompt**: **Combine** the query and the retrieved chunks into a prompt.

3. Generation pineline:

- **LLM**: Generate a response based on the augmented prompt.
- **Response**: Return the response to the user.
