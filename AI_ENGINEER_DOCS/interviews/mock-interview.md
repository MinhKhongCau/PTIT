# Mock Interview: AI Engineer Intern

**Role:** Candidate (AI Engineer Intern)
**Language:** Vietnamese / English Mixed

---

## Question 1: Model Training Accuracies
**Interviewer:** Consider this sequence of model accuracies during training:
- Train Acc (Epoch 1-9): 0.6, 0.64, 0.7, 0.76, 0.85, 0.88, 0.9, 0.93, 0.96
- Val Acc (Epoch 1-9): 0.52, 0.59, 0.66, 0.7, 0.76, 0.83, 0.79, 0.74, 0.7

What is the most likely problem occurring in this model? Name two techniques you would apply to reduce this problem in this scenario. What is the best epoch to select the model for deployment? Why? If validation accuracy kept increasing together with training accuracy, what would that indicate about the model?

**Candidate:**
Phân tích tình huống đang gặp phải: Tập Train đang tăng lên từ 0.64 -> 0.96 một cách liên tục. Nhưng tập test lại tăng đến 1 ngưỡng 0.83 ở epoch thứ 6 và nó giảm dần về sau. Tình huống này mô hình đang dần bị Overfitting và BIAS đang dần tiến xa khỏi các giá trị nhãn thực tế. Hiện tượng này gọi là quá khớp dữ liệu khi mà ta đưa vào mô hình khác những giá trị nó học thì nó không còn học đúng nữa.

Để giải quyết bài toán này sẽ có 2 cách: 
1. Phương pháp thu thập thêm dữ liệu: Giải thích - Có thể dữ liệu quá ít hay nó lặp lại quá nhiều dẫn đến nó “Chai lì” với các dữ liệu cũ.
2. Sử dụng 1 mô hình khác mà nó phù hợp hơn với bài toán đang đặt: Giải thích - Mô hình có thể quá đơn giản để nó học được 1 lượng lớn dữ liệu hay mô hình nó quá lớn nhưng nó học đi học lại quá ít dữ liệu làm cho mô hình bị overfitting.

Epoch tốt nhất: Epoch số 6 để sử dụng production. Vì nó là epoch cho ra giá trị mà BIAS và VARIANCE nằm ở mức cân bằng nhất.

Nếu validation accuracy tiếp tục tăng cùng training accuracy: Điều đó chỉ ra Mô hình học tốt. Tiếp tục kiểm tra mô hình với các bộ dataset khác để nó có thể tăng sự tin tưởng hơn.

---

## Question 2: Imbalanced Dataset
**Interviewer:** You are solving a binary classification problem: 90% negative, 10% positive. Describe two precise training techniques to handle imbalance. Explain mathematically or intuitively why it works. Would you apply it at test time? Why or why not?

**Candidate:**
Để xét trường hợp này cần phải xác định mình đang gặp phải vấn đề ở đâu, tài nguyên mình bỏ ra như thế nào, bài toán nó đang phức tạp hay là đơn giản. Bộ dataset có nhiều hay không?
Trường hợp này theo lý thuyết thì nó đang mất cân bằng dữ liệu. Nhưng nếu cho nó học thì vẫn có thể được nếu bài toán và quy mô dự án đang nhỏ. Tuy nhiên tiềm ẩn rất nhiều rủi ro khi sử dụng cách làm này. Vì nó không đủ căn cứ để đánh giá mô hình này có hoạt động tốt về sau không.
Nếu để giải quyết vấn đề này thì cách tốt nhất là thu thập thêm dữ liệu. Nếu không có đủ thời gian và kinh phí thì có thể sử dụng các phương pháp để tăng dữ liệu như CROSS... *(Câu trả lời chưa hoàn thành)*

---

## Question 3: Evaluation Metrics for Fraud Detection
**Interviewer:** You are building an AI system to detect fraudulent invoices. Missing fraud is very costly (each missed fraud costs $50,000), while false alarms cost $500 to investigate. Which of the following is the most appropriate evaluation metric: Accuracy, Precision, Recall, or Loss value? Explain why.

**Candidate:**
Chọn Recall.
Vì trong bài toán này phần ưu tiên chắc chắn là “Không để bỏ sót bất kỳ trường hợp nào”. Nên là chọn Recall vì nó là giá trị Nhãn đúng so với toàn bộ tập dữ liệu xét. Nếu nó càng tiến về 1 thì chi phí phạt sẽ càng thấp.

---

## Question 4: 1x1 Convolution
**Interviewer:** What is the purpose of using 1×1 convolution? The answer must include: The primary computational benefit, an example use case in a popular architecture, and how it affects model capacity vs. computation trade-off.

**Candidate:**
Mục đích của lớp convolution 1x1 là: nhân tích chập với ma trận 1x1 với giá trị đầu vào. Từ đó giảm thiểu số chiều, độ lớn của các layer trước đó trước khi đi qua các Layer tiếp theo. *(Câu trả lời chưa hoàn thành cho các ý còn lại)*

---

## Question 5: BERT vs Generative LLM Embeddings
**Interviewer:** Explain the difference between BERT-style embedding models and Generative LLM embeddings. The answer must include Architecture, Model size, and Training Objective.

**Candidate:**
Mô hình BERT là mô hình dựa trên Transformer để nhận biết chữ viết, và nó sẽ dự đoán các giá trị tiếp theo dựa trên các giá trị trước đó và nó có thể nhìn nhiều chiều. LLM thì sinh dữ liệu dựa trên token và nó thiết kế theo kiểu Sequential.
Thông thường mô hình BERT sẽ chiếm ít tài nguyên hơn là LLM vì nó có ít Layer. *(Câu trả lời cần bổ sung thêm chi tiết cụ thể về Training Objective và kích thước cụ thể)*

---

## Question 6: Mitigating Hallucinations in Production
**Interviewer:** Your team deploys a Vietnamese customer-support LLM. Answers are fluent and polite but sometimes contain subtle wrong facts (hallucinations). Users rarely report errors immediately. You cannot retrain the base model for now. Propose a practical solution to reduce hallucinations in production under these constraints.

**Candidate:**
Đầu tiên phải xác định model hiện đang hỗ trợ công nghệ này là gì. Nó học được dữ liệu như thế nào rồi, tài liệu tiếng việt đã có bao nhiêu, Tiếng anh hay tiếng nước ngoài đã được học như thế nào. Từ đó để tăng “Độ tin cậy” thì mình sẽ có biện pháp xử lý phù hợp.
1. Train (Fine-tune/RAG) thêm tài liệu có kiểm chứng.
2. Giám sát các thứ mà nó học để tránh thông tin sai lệch.
Vì nó đã được release thì sẽ chỉ có thể cải thiện độ trễ bằng cách caching hay các kỹ thuật như generative dựa trên token...

---

## Question 7: RAG Pipeline Optimization
**Interviewer:** A flower shop needs a chatbot to help customers find information about its products. The proposed RAG pipeline uses an LLM to rewrite the message, retrieves chunks, uses an LLM to re-rank chunks sequentially, and then uses another LLM for the final answer. What issues are there in this pipeline and how to improve it?

**Candidate:**
Vấn đề: Nó gửi đến quá nhiều LLM để xử lý. Nhưng có 1 vấn đề là ChatBot thì người ta muốn câu trả lời ngay lập tức -> dẫn đến điểm yếu lớn nhất là vấn đề độ trễ (latency).

---

## Question 8: RAG Document Chunking Challenges
**Interviewer:** You are working on a RAG system with 300 Markdown documents lacking headings. Issues observed: 1. Long lists get truncated. 2. Code blocks are distorted. 3. Content at the end of documents isn't retrieved well. How do you solve those issues?

**Candidate:**
*(Chưa có câu trả lời từ ứng viên)*

---

## Question 9: Decision Trees, Random Forest & Boosting
**Interviewer:** Analyze the advantages and limitations (especially overfitting) of the traditional Decision Tree algorithm. Explain how Random Forest and Boosting algorithms address these.

**Candidate:**
Decision Tree: Đơn giản, dễ triển khai. Nó có thể học với Variance thấp. *(Câu trả lời chưa hoàn thành)*

---

## Question 10: RNN and Vanishing Gradients
**Interviewer:** For sequential data, why is the architecture of RNNs suitable? Basic RNNs suffer from "vanishing gradient". Explain the cause and how LSTM addresses it.

**Candidate:**
RNN là mô hình phù hợp hơn vì nó... *(Câu trả lời chưa hoàn thành)*
