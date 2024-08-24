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

c
Copy code
// Enable clock for UART1
RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
// Configure GPIO for UART1 TX and RX
GPIOA->CRH |= (GPIO_CRH_MODE9_1 | GPIO_CRH_CNF9_1) | (GPIO_CRH_CNF10_0);
// Configure UART1
USART1->BRR = 72000000 / 9600; // Baud rate
USART1->CR1 = USART_CR1_TE | USART_CR1_RE | USART_CR1_UE; // Enable TX, RX, and UART
Sử Dụng UART
Gửi Dữ Liệu:

c
Copy code
while (!(USART1->SR & USART_SR_TXE)); // Wait until TXE flag is set
USART1->DR = data; // Send data
Nhận Dữ Liệu:

c
Copy code
while (!(USART1->SR & USART_SR_RXNE)); // Wait until RXNE flag is set
data = USART1->DR; // Read received data
2. Cấu Hình SPI (Serial Peripheral Interface)
Cấu Hình SPI
Chọn SPI Peripheral:

Xác định SPI nào bạn sẽ sử dụng (SPI1, SPI2, v.v.).
Cấu Hình GPIO:

Chọn chân GPIO cho SCK, MOSI, MISO, và (nếu cần) SS.
Thiết lập các chân GPIO cho chế độ Alternate Function (AF) để phù hợp với SPI.
Cấu Hình SPI:

Ba cấu hình chính: Baud rate, Data size, Clock polarity (CPOL), Clock phase (CPHA), và Frame format.
Ví dụ cấu hình SPI1:

c
Copy code
// Enable clock for SPI1
RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
// Configure GPIO for SPI1
GPIOA->CRL |= (GPIO_CRL_MODE5 | GPIO_CRL_CNF5_1) | (GPIO_CRL_CNF6_1 | GPIO_CRL_MODE6) | (GPIO_CRL_CNF7_1 | GPIO_CRL_MODE7);
// Configure SPI1
SPI1->CR1 = SPI_CR1_MSTR | SPI_CR1_BR_0 | SPI_CR1_SSI | SPI_CR1_SSM | SPI_CR1_SPE; // Master mode, Baud rate, Enable
Sử Dụng SPI
Gửi Dữ Liệu:

c
Copy code
while (!(SPI1->SR & SPI_SR_TXE)); // Wait until TXE flag is set
SPI1->DR = data; // Send data
Nhận Dữ Liệu:

c
Copy code
while (!(SPI1->SR & SPI_SR_RXNE)); // Wait until RXNE flag is set
data = SPI1->DR; // Read received data
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

c
Copy code
// Enable clock for I2C1
RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
// Configure GPIO for I2C1
GPIOB->CRL |= (GPIO_CRL_CNF6_1 | GPIO_CRL_MODE6_1) | (GPIO_CRL_CNF7_1 | GPIO_CRL_MODE7_1);
// Configure I2C1
I2C1->CR1 = I2C_CR1_PE; // Enable I2C1
I2C1->CR2 = 36; // Clock control (based on PCLK1)
I2C1->CCR = 180; // Timing settings
I2C1->TRISE = 37; // Rise time
Sử Dụng I2C
Gửi Dữ Liệu:

c
Copy code
I2C1->CR1 |= I2C_CR1_START; // Send start condition
while (!(I2C1->SR1 & I2C_SR1_SB)); // Wait for start condition
I2C1->DR = address; // Send address
while (!(I2C1->SR1 & I2C_SR1_ADDR)); // Wait for address sent
// Send data
I2C1->DR = data;
while (!(I2C1->SR1 & I2C_SR1_BTF)); // Wait until byte transfer finished
I2C1->CR1 |= I2C_CR1_STOP; // Send stop condition
Nhận Dữ Liệu:

c
Copy code
I2C1->CR1 |= I2C_CR1_START; // Send start condition
while (!(I2C1->SR1 & I2C_SR1_SB)); // Wait for start condition
I2C1->DR = address | 1; // Send address for read
while (!(I2C1->SR1 & I2C_SR1_ADDR)); // Wait for address sent
data = I2C1->DR; // Read data
I2C1->CR1 |= I2C_CR1_STOP; // Send stop condition
