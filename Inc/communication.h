#pragma once

void msg_init();
void msg_recv(int type, void* msg);
void task_uart(void *huart1);
void ack();
void send(int type, void *data);
