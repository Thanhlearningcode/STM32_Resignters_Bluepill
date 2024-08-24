/// TIMER
Bước 1: Chọn xung clock => tính ARR,PSC,CNT
// CNT là biến đếm, ARR là giới hạn đếm, PSC là bộ chia
Bước 2 : nhìn vào sơ đồ RCC để cấu hình TIM nào
// Giả sử t dùng 72MHZ ( mặc đinh nếu ko setting thông số clock) thì công thức T=1/f
// Chọn T=1s, => ftimer= Fclock/ (PSC+1) == 72/ (71+1)=1 ms => ftimer(ARR)== 1000
// Chọn PSC=15,CNT=0,ARR=999 lí do CNT đếm từ 0
Bước 3 : Setting bit7   CR1 : ARR auto-reload
         Setting bit4   CR1 : counter up
         Setting bit2,1 CR1 : Store giá trị đếm
         Setting bit0   CR2 : setting bit UG 
         setting bit0   CR1 : Enable timer

/// PWM
Bước 1: Y hệt timer
Bước 2 : Y hệt Timer
Bước 3: Configure GPIO là AF
// Giả sử dùng channel 1 thì CCMR1
Bước 4: Configure channel1 là PWMmode1 110 ( lí do là nó đếm lên hết)
Bước 5: Chọn CC1 là output. Và cho TIM->CCRx = percent ( Parameter)
Bước 6: ENABLE capture/compare . CCER =1;
Bước 7: ENABLE counter
