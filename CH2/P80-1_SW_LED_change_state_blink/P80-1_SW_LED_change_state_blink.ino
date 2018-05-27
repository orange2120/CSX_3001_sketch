/*
*P80-1
*設計Arduino 程式，使用一個按鍵開關控制一個LED 閃爍與暗。每按一下按鍵開關，LED 的狀態將會改變。
*若LED 原來狀態為暗，按一下按鍵開關時，LED 閃爍，
*若LED 原來狀態為閃爍，按一下按鍵開關時，LED 暗。
*/

const uint8_t led = 13;
const uint8_t sw = 9; //宣告開關輸入腳位

#define BLINK_INTERVAL 100 //ms，LED閃爍的間隔
#define DEBOUNCE_INTERVAL 20 //ms，開關去彈跳的間隔

unsigned long last_blink = 0;
bool led_state = 0;

bool sw_state = 0; //0代表斷開，1代表接通
bool temp_state = 0; //紀錄開關暫態

void setup()
{
	pinMode(sw, INPUT_PULLUP); //使用內建上拉電阻
	pinMode(led, OUTPUT);
	
	digitalWrite(led, LOW);
}

void loop()
{
	unsigned long now = millis();
	temp_state = digitalRead(sw);
	if(!temp_state)               //開關去彈跳
	{
		delay(DEBOUNCE_INTERVAL);
		while(!digitalRead(sw));
		sw_state = !sw_state;
	}

	if(now-last_blink >= BLINK_INTERVAL) //每隔固定時間檢查是否需要閃爍
	{
		digitalWrite(led, led_state & sw_state);
		last_blink = now; //更新最後一次執行時間
		led_state = !led_state; //LED狀態反轉
	}
}