# Copyright (c) 2026 Author. All Rights Reserved.

## Caching 
- Caching lưu trữ tạm thời dữ liệu thường xuyên truy cập vào bộ nhớ cục bộ. Giúp tránh việc tính toán lại hoặc truy vấn database mất thời gian. 

## The caching how to processing.

- Cache into RAM (Redis, Memcached)
- Cache in CPU 

## Caching stategy (Chiến lược cache)

1. Cache-Aside 
- Ứng dụng kiểm tra trong cache trước:
  |-Nếu có trả về luôn
  |-Nếu không ứng dụng đọc query vào db, ghi vào cache -> trả về.
- Ưu điểm: Tiết kiệm RAM.
- Nhược điểm: Độ trễ cao ở lần đầu **đọc**, nguy cơ dữ liệu bị cũ nếu DB thay đổi.
- Phù hợp cho dữ liệu ít thay đổi liên tục nhưng được lấy nhiều như (thông tin tài khoản, danh sách món ăn, vật liệu,...) 
2. Write-Through
- Ứng dụng ghi vào cache đầu tiên, và cache ghi vào DB trước khi báo thành công.
- Ưu điểm: Dữ liệu luôn nhất quán.
- Nhược điểm: Độ trễ cao mỗi lần **ghi**.
- Phù hợp cho dữ liệu cần tính nhất quán cao, chấp nhận độ trễ khi ghi như (đơn hàng, hóa đơn,...)
3. Write-Back 
- Ứng dụng ghi vào Cache và báo thành công ngay. Cache sẽ gom lại các thay đổi và ghi bất đồng bộ.
- Ưu điểm: Tốc độ ghi nhanh, tránh làm tắc nghẽn hệ thống.
- Nhược điểm: Nguy cơ mất mát dữ liệu nếu chưa kịp ghi vào DB.
- Phù hợp cho các loại dữ liệu có thể không cập nhật ngay như (Sửa profile,...)

4. Refresh-Ahead
- Hệ thống sẽ dự đoán dữ liệu sắp hết hạn (TTL) và tự làm mới từ DB.
- Ưu điểm: Nhanh, gọn, rõ ràng, dễ quản lý trong code.
- Nhược điểm: Dữ liệu có thể bị trễ trong khoảng (1-2s) trong khi cập nhật.
- Phù hợp cho cache các loại dữ liệu phân tích có thể đánh đổi tính nhất quán (Dashboard, analyze,...). Cache ở phía Frontend để người dùng truy cập một cách nhanh chóng (React Query, Tanstack,...)
