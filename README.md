Cấu Hình Timer
Bước 1: Tính Toán Các Tham Số

Chọn Tần Số Xung Clock: Xác định tần số của xung clock cho timer. Ví dụ, giả sử xung clock là 72 MHz (tần số mặc định nếu không cấu hình khác).

Tính Toán ARR và PSC:

ARR (Auto-Reload Register): Xác định giá trị giới hạn đếm của timer.
PSC (Prescaler): Xác định giá trị phân chia tần số của clock.
CNT (Counter Register): Giá trị bắt đầu của bộ đếm, thường là 0.
Ví dụ: Nếu bạn muốn có một khoảng thời gian T = 1 giây, thì tần số của timer sau phân chia là 
𝑓
timer
=
𝑓
clock
PSC
+
1
f 
timer
​
 = 
PSC+1
f 
clock
​
 
​
 . Với 
𝑓
clock
=
72
 MHz
f 
clock
​
 =72 MHz và PSC = 71, thì 
𝑓
timer
=
72
 MHz
72
=
1
 kHz
f 
timer
​
 = 
72
72 MHz
​
 =1 kHz.

Để đạt được một khoảng thời gian 1 giây, ARR phải là 
𝑓
timer
T
−
1
T
f 
timer
​
 
​
 −1, tương đương với 1000 - 1 = 999.

Bước 2: Cấu Hình Các Đăng Ký (Registers)

CR1 (Control Register 1):

Bit 7: Đặt chế độ ARR tự động nạp lại.
Bit 4: Chế độ đếm lên (Counter Up).
Bit 2 và Bit 1: Lưu giá trị đếm (Update).
CR2 (Control Register 2):

Bit 0: Kích hoạt cập nhật (Update Generation).
Đặt Bit 0 CR1: Kích hoạt timer.

Cấu Hình PWM
Bước 1: Cấu Hình Timer (Tương Tự Như Bước 1 Trên)

Bước 2: Cấu Hình Timer (Tương Tự Như Bước 2 Trên)

Bước 3: Cấu Hình GPIO

Thiết lập Chế Độ Alternate Function (AF): Đảm bảo chân GPIO tương ứng với PWM ở chế độ AF.
Bước 4: Cấu Hình PWM Mode

CCMR1 (Capture/Compare Mode Register 1):
Chọn chế độ PWM Mode 1 (Cài đặt 110) để đếm từ 0 đến ARR.
Bước 5: Cấu Hình Channel

CCRx (Capture/Compare Register x): Đặt giá trị PWM cho kênh (percent) cần thiết.
Bước 6: Kích Hoạt Capture/Compare

CCER (Capture/Compare Enable Register): Đặt giá trị CCER = 1 để kích hoạt chức năng capture/compare.
Bước 7: Kích Hoạt Timer

CR1 (Control Register 1): Đặt bit 0 UG để kích hoạt cập nhật (Update Generation) và bật bộ đếm.


1. Cấu Hình UART (Universal Asynchronous Receiver/Transmitter)
Cấu Hình UART
Chọn UART Peripheral:

Xác định UART nào bạn sẽ sử dụng (UART1, UART2, v.v.).
Cấu Hình GPIO:

Chọn chân GPIO cho TX và RX.
Thiết lập các chân GPIO cho chế độ Alternate Function (AF) để phù hợp với UART.
Cấu Hình UART:

Ba cấu hình chính: Baud rate, Word length, Stop bits, Parity, và Flow control.
Ví dụ cấu hình UART1 với baud rate 9600:

Cấu Hình SPI
Chọn SPI Peripheral:

Xác định SPI nào bạn sẽ sử dụng (SPI1, SPI2, v.v.).
Cấu Hình GPIO:

Chọn chân GPIO cho SCK, MOSI, MISO, và (nếu cần) SS.
Thiết lập các chân GPIO cho chế độ Alternate Function (AF) để phù hợp với SPI.
Cấu Hình SPI:

Ba cấu hình chính: Baud rate, Data size, Clock polarity (CPOL), Clock phase (CPHA), và Frame format.
Ví dụ cấu hình SPI1:


Sử Dụng SPI
Gửi Dữ Liệu:

3. Cấu Hình I2C (Inter-Integrated Circuit)
Cấu Hình I2C
Chọn I2C Peripheral:

Xác định I2C nào bạn sẽ sử dụng (I2C1, I2C2, v.v.).
Cấu Hình GPIO:

Chọn chân GPIO cho SDA và SCL.
Thiết lập các chân GPIO cho chế độ Alternate Function (AF) để phù hợp với I2C.
Cấu Hình I2C:

Ba cấu hình chính: Clock speed, Addressing mode, và Digital noise filter.
Ví dụ cấu hình I2C1:

