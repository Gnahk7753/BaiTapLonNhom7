# 🏢 Phần Mềm Quản Lý Chung Cư

> Dự án bài tập lớn - Nhóm 7  
> Ngôn ngữ lập trình: **C**

---

## 📋 Giới thiệu

Phần mềm Quản Lý Chung Cư là ứng dụng console được xây dựng bằng ngôn ngữ C, hỗ trợ quản lý thông tin cư dân, tài khoản người dùng và các hoạt động hành chính trong một tòa nhà chung cư. Hệ thống phân quyền ba cấp (Admin, Quản lý và Cư dân) giúp đảm bảo tính bảo mật và phân công công việc rõ ràng.

---

## ✨ Tính năng

- **Đăng nhập / Xác thực** - Hệ thống đăng nhập phân quyền cho Admin, Quản lý và Cư dân
- **Quản lý cư dân** - Thêm, sửa, xóa, tìm kiếm thông tin cư dân
- **Quản lý tài khoản** - Quản lý tài khoản Admin, tài khoản Quản lý và tài khoản Cư dân
- **Quản lý tỉnh/thành phố** - Dữ liệu địa chỉ đầy đủ 63 tỉnh thành Việt Nam
- **Lịch sử hoạt động** - Ghi nhật ký các thao tác trong hệ thống
- **Giao diện console** - Menu điều hướng trực quan, dễ sử dụng

---

## 🗂️ Cấu trúc dự án

```
BaiTapLonNhom7/
├── main.c                      # Điểm khởi chạy chương trình
│
├── Modules/                    # Các module chức năng
│   ├── Admin.c / Admin.h       # Chức năng dành cho Admin
│   ├── Login.c / Login.h       # Xử lý đăng nhập & xác thực
│   ├── Manage.c / Manage.h     # Chức năng dành cho Quản lý
│   ├── Resident.c / Resident.h # Quản lý thông tin cư dân
│   └── Utils.c / Utils.h       # Các hàm tiện ích dùng chung
│
├── Data/                       # Dữ liệu lưu trữ (file text)
│   ├── History.txt             # Lịch sử hoạt động hệ thống
│   ├── Account/
│   │   ├── Admin/
│   │   │   └── admin.txt       # Thông tin tài khoản Admin
│   │   └── Manage/
│   │       └── manage.txt      # Thông tin tài khoản Quản lý
│   └── Province/               # Dữ liệu 63 tỉnh/thành phố
│       ├── 001.txt             # Hà Nội
│       ├── 002.txt             # Hồ Chí Minh
│       └── ...                 # (và các tỉnh thành khác)
│
└── FloorList/                  # Danh sách các tầng
    ├── Floor1/                 # Tầng 1
    │   ├── P101/               # Phòng 101
    │   │   ├── resident1.txt   # Thông tin cư dân 1
    │   │   ├── resident2.txt   # Thông tin cư dân 2
    │   │   └── ...
    │   ├── P102/               # Phòng 102
    │   │   └── ...
    │   └── ...
    ├── Floor2/
    │   └── ...
    └── ...
```

---

## 🔐 Phân quyền hệ thống

|       Vai trò        |                       Quyền hạn                           |
|----------------------|-----------------------------------------------------------|
| **Admin**            | Quản lý tài khoản, xem toàn bộ dữ liệu, cấu hình hệ thống |
| **Quản lý (Manage)** | Quản lý cư dân, cập nhật thông tin, xem báo cáo           |
| **Cư dân (Resident)**| Xem thông tin cá nhân, xem hóa đơn                        |

---

## ⚙️ Yêu cầu hệ thống

- Trình biên dịch C: **GCC** (khuyến nghị) hoặc tương đương
- Hệ điều hành: Windows / Linux / macOS
- Không yêu cầu thư viện ngoài (chỉ dùng thư viện chuẩn C)

---

## 🚀 Hướng dẫn cài đặt & chạy

### 1. Clone hoặc giải nén dự án

```bash
# Giải nén file RAR
unrar x BaiTapLonNhom7.rar

# Di chuyển vào thư mục dự án
cd BaiTapLonNhom7
```

### 2. Biên dịch chương trình

```bash
gcc main.c Modules/Admin.c Modules/Login.c Modules/Manage.c Modules/Resident.c Modules/Utils.c -o QuanLyChungCu
```

Hoặc sử dụng wildcard:

```bash
gcc main.c Modules/*.c -o QuanLyChungCu
```

### 3. Chạy chương trình

```bash
# Linux / macOS
./QuanLyChungCu

# Windows
QuanLyChungCu.exe
```

---

## 🖥️ Hướng dẫn sử dụng

1. **Khởi động** chương trình, màn hình đăng nhập sẽ hiện ra
2. **Nhập tên đăng nhập và mật khẩu** theo vai trò (Admin, Quản lý hoặc Cư dân)
3. **Chọn chức năng** từ menu tương ứng với quyền hạn của tài khoản
4. **Thực hiện các thao tác** quản lý cư dân, tài khoản, hoặc xem lịch sử...

### Tài khoản Admin mặc định

```bash
# Username
admin

# Password
Admin123@
```

### Tài khoản Quản lý mặc định

```bash
# Username
manage

# Password
Manage123@
```

> **Lưu ý:** Sau khi đăng nhập, vui lòng đổi mật khẩu.

---

## 👥 Thành viên nhóm 7

| STT |         Họ và tên         |    MSSV     |                 Vai trò                |
|-----|---------------------------|-------------|----------------------------------------|
| 1   | Nguyễn Trần Duy Bảo       | 6651071004  | Leader, Code chức năng của Quản lý     |
| 2   | Nguyễn Văn Tuấn Khang     | 6651071031  | Làm UI, Code cơ chế đăng nhập          |
| 3   | Phạm Đức Cường            | 6651071007  | Code chức năng của Cư dân              |
| 4   | Nguyễn Lê Văn Đài         | 6651071012  | Code chức năng của Admin               |

---

## 📌 Ghi chú phát triển

- Dữ liệu được lưu trữ dưới dạng file `.txt` — đơn giản, không cần cơ sở dữ liệu
- Dữ liệu tỉnh thành sử dụng mã số theo chuẩn phân chia hành chính Việt Nam
- Lịch sử hoạt động được ghi tự động vào `Data/History.txt`

---

## 📄 Giấy phép

Dự án được thực hiện phục vụ mục đích học tập — Bài Tập Lớn môn Kỹ thuật Lập trình / Lập trình C.
