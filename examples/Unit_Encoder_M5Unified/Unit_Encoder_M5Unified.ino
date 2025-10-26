#include <M5Unified.h>
#include <Unit_Encoder.h>

M5Canvas canvas(&M5.Display);
Unit_Encoder sensor;

void setup() {
    auto cfg = M5.config();
    cfg.clear_display = true;
    cfg.serial_baudrate = 115200;
    M5.begin(cfg);
    sensor.begin();
    canvas.createSprite(M5.Display.width(), 80);
    canvas.setTextSize(2);
}

signed short int last_value = 0;

void loop() {
    signed short int encoder_value = sensor.getEncoderValue();
    bool btn_status                = sensor.getButtonStatus();
    if (last_value != encoder_value) {
        Serial.println(encoder_value);
        if (last_value > encoder_value) {
            sensor.setLEDColor(1, 0x000011);
        } else {
            sensor.setLEDColor(2, 0x111100);
        }
        last_value = encoder_value;
    } else {
        sensor.setLEDColor(0, 0x001100);
    }
    if (!btn_status) {
        sensor.setLEDColor(0, 0xC800FF);
    }
    canvas.fillSprite(BLACK);
    canvas.setCursor(0, 0);
    canvas.print("BTN: ");
    canvas.println(btn_status);
    canvas.print("ENC: ");
    canvas.println(encoder_value);
    canvas.pushSprite(0, 0);
    delay(20);
}