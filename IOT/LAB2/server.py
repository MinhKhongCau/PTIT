from flask import Flask, request, render_template, jsonify
from flask_socketio import SocketIO, emit
import os
import cv2
import numpy as np
from until import crop_face_and_predict


app = Flask(__name__)
socketio = SocketIO(app, cors_allowed_origins="*")

# --- Giao diện chính ---
@app.route("/")
def index():
    return render_template("index.html")

@socketio.on('connect')
def connected():
    print("ESP32 connected")

@socketio.on('message')
def handle_message(data):
    print("Text:", data)

@socketio.on('binary')
def handle_binary(data):
    # Chuyển bytes thành ảnh
    npimg = np.frombuffer(data, np.uint8)
    frame = cv2.imdecode(npimg, cv2.IMREAD_COLOR)
    label, (x1, y1, x2, y2) = crop_face_and_predict(frame)

    if frame is not None:
        cv2.imshow("ESP32 Stream", frame)
        cv2.waitKey(1)

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000)
