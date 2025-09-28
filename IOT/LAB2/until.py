import joblib
from tensorflow.keras.models import load_model
from sklearn.metrics import accuracy_score
import numpy as np
import cv2
from ultralytics import YOLO

MODEL_SVM_PATH = "model/svm_model.pkl"
MODEL_RESNET50_FE_PATH = "model/resnet50_feature_extractor.h5"


# Load models
svm = joblib.load(MODEL_SVM_PATH)
resnet50_fe_model = load_model(MODEL_RESNET50_FE_PATH)
yolo = YOLO("yolov8n-face.pt")  # yolov8n-face là version nhẹ

# Predict 1 image function
def predict_image(img=None):
    img = cv2.resize(img, (224, 224))
    img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    img = np.expand_dims(img, axis=0)
    
    # Extract features
    features = resnet50_fe_model.predict(img)
    
    # Predicts SVM
    pred = svm.predict(features)
    # {"with_mask", "without_mask", "incorrect_mask"}
    return pred[0]

def crop_face_and_predict(img):
    # Detect faces
    results = yolo.predict(img, conf=0.5, verbose=False)  # conf=threshold
    for r in results[0].boxes:  # results[0].boxes: list of Box objects
        x1, y1, x2, y2 = map(int, r.xyxy[0])  # bounding box
        face = img[y1:y2, x1:x2]

        # Dự đoán nhãn mask bằng SVM
        label = predict_image(face)
    return label, (x1, y1, x2, y2)

def predict_batch(X_test, y_test):
    preds = []

    print(f"[🔍] Đang dự đoán {len(X_test)} ảnh test...")
    for i, img in enumerate(X_test):
        try:
            pred = predict_image(img)
            preds.append(pred)
        except Exception as e:
            print(f"[⚠️] Lỗi tại ảnh {i}: {e}")
            preds.append("unknown")

    # Tính accuracy
    preds = np.array(preds)
    y_test = np.array(y_test)

    # Lọc ảnh hợp lệ (không bị 'unknown')
    valid_idx = preds != "unknown"
    acc = accuracy_score(y_test[valid_idx], preds[valid_idx])

    print(f"\n✅ Độ chính xác (Accuracy): {acc * 100:.2f}%")
    return preds