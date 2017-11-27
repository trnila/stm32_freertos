#include "uart_hal_transport.h"

#include <cstdio>

using namespace erpc;

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

static volatile bool s_isTransferReceiveCompleted = false;
static volatile bool s_isTransferSendCompleted = false;

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

UartHalTransport::UartHalTransport(UART_HandleTypeDef *uartDrv)
: m_uartDrv(uartDrv)
{
}

UartHalTransport::~UartHalTransport()
{
}

/* Transfer callback */
void TransferCallback(uint32_t event)
{
    /*if (event == ARM_USART_EVENT_SEND_COMPLETE)
    {
        s_isTransferSendCompleted = true;
    }

    if (event == ARM_USART_EVENT_RECEIVE_COMPLETE)
    {
        s_isTransferReceiveCompleted = true;
    }*/
}

erpc_status_t UartHalTransport::init()
{
	return kErpcStatus_Success;
}

erpc_status_t UartHalTransport::underlyingReceive(uint8_t *data, uint32_t size)
{
    s_isTransferReceiveCompleted = false;

    HAL_UART_Receive(m_uartDrv, data, size, HAL_MAX_DELAY);

    return kErpcStatus_Success;
}

erpc_status_t UartHalTransport::underlyingSend(const uint8_t *data, uint32_t size)
{
    s_isTransferSendCompleted = false;

    HAL_UART_Transmit(m_uartDrv, (uint8_t*) data, size, HAL_MAX_DELAY);

    return kErpcStatus_Success;
}
