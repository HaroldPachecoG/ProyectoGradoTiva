/*
 * Copyright (c) 2015-2016, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== httpgetCC3100.c ========
 *  HTTP Client GET example using CC3100
 */
#include <string.h>

/* XDCtools Header files */
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>

/* TI-RTOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/drivers/GPIO.h>
#include <ti/net/http/httpcli.h>

#include <simplelink.h>

/* Example/Board Header file */
#include "Board.h"

/* Local Platform Specific Header file */
#include "sockets.h"

#define REQUEST_URI       "/"
#define USER_AGENT        "HTTPCli (ARM; TI-RTOS)"
#define HTTPTASKSTACKSIZE 2048

const char HOSTNAME[] = "www.example.com";
char task0Stack[HTTPTASKSTACKSIZE];
Task_Struct task0Struct;

extern bool smartConfigFlag;

/*
 *  ======== gpioButtonFxn ========
 *  Callback function for the GPIO interrupt on Board_BUTTON0.
 */
void gpioButtonFxn(unsigned int index)
{
    /* Begin smart config process */
    smartConfigFlag = true;
}

/*
 *  ======== printError ========
 */
void printError(char *errString, int code)
{
    System_printf("\nError! code = %d, desc = %s\n", code, errString);
    BIOS_exit(code);
}

/*
 *  ======== httpFxn ========
 *  Makes an HTTP GET request
 */
void httpValidar(int valor)
{
    #define REQUEST_URI       "/tarjeta_vehiculo/11/"
    //#define REQUEST_URI       "https://proyectousbbog.000webhostapp.com/conexion_out.php?id=1"
    #define USER_AGENT        "HTTPCli (ARM; TI-RTOS)"
    const char HOSTNAME[] = "jdanielcl.pythonanywhere.com";
    //const char HOSTNAME[] = "proyectousbbog.000webhostapp.com";
    bool moreFlag = false;
    char data[64];
    int ret;
    int len;
    struct sockaddr_in addr;

    HTTPCli_Struct cli;
    HTTPCli_Field fields[3] = {
        { HTTPStd_FIELD_NAME_HOST, HOSTNAME },
        { HTTPStd_FIELD_NAME_USER_AGENT, USER_AGENT },
        { NULL, NULL }
    };
    /*HTTPCli_Field fields[2] = {
            { HTTPStd_FIELD_NAME_HOST, HOSTNAME },
            { NULL, NULL }
        };
*/
    System_printf("Sending a HTTP GET request to '%s'\n", HOSTNAME);
    System_flush();

    HTTPCli_construct(&cli);

    HTTPCli_setRequestFields(&cli, fields);

    ret = HTTPCli_initSockAddr((struct sockaddr *)&addr, HOSTNAME, 0);
    if (ret < 0) {
        printError("httpTask: address resolution failed", ret);
    }

    ret = HTTPCli_connect(&cli, (struct sockaddr *)&addr, 0, NULL);
    if (ret < 0) {
        printError("httpTask: connect failed", ret);
    }
    System_printf("Request '%s'\n", REQUEST_URI);
    System_flush();
    ret = HTTPCli_sendRequest(&cli, HTTPStd_GET, REQUEST_URI, false);
    if (ret < 0) {
        printError("httpTask: send failed", ret);
    }

    ret = HTTPCli_getResponseStatus(&cli);
    /*if (ret != HTTPStd_OK) {
        printError("httpTask: cannot get status", ret);
    }*/

    System_printf("HTTP Response Status Code: %d\n", ret);

    ret = HTTPCli_getResponseField(&cli, data, sizeof(data), &moreFlag);
    if (ret != HTTPCli_FIELD_ID_END) {
        printError("httpTask: response field processing failed", ret);
    }
    len = 0;
    do {
        ret = HTTPCli_readResponseBody(&cli, data, sizeof(data), &moreFlag);
        if (ret < 0) {
            printError("httpTask: response body processing failed", ret);
        }

        len += ret;
    }while (moreFlag);
    System_printf("Body request '%s'\n", data);
    System_flush();

    System_printf("Recieved %d bytes of payload\n", len);
    System_flush();

    HTTPCli_disconnect(&cli);
    HTTPCli_destruct(&cli);
}
void httpEntrada(char valor)
{
    //char id;
    //#define REQUEST_URI       "/conexion_in.php?id=2"
    //iota(valor,id);
    char numeros[] ={'/','c','o','n','e','x','i','o','n','_','i','n','.','p','h','p','?','i','d','='};
    numeros[20]=valor;
    //#define REQUEST_URI       "/conexion_out.php?id=1"
    #define REQUEST_URI       numeros
    #define USER_AGENT        "HTTPCli (ARM; TI-RTOS)"
    const char HOSTNAME[] = "proyectousbbog.000webhostapp.com";
    bool moreFlag = false;
    char data[64];
    int ret;
    int len;
    struct sockaddr_in addr;

    HTTPCli_Struct cli;
    HTTPCli_Field fields[3] = {
        { HTTPStd_FIELD_NAME_HOST, HOSTNAME },
        { HTTPStd_FIELD_NAME_USER_AGENT, USER_AGENT },
        { NULL, NULL }
    };
    System_printf("Sending a HTTP GET request IN to '%s'\n", HOSTNAME);
    System_flush();

    //Crea un nuevo objeto de instancia en la estructura proporcionada
    HTTPCli_construct(&cli);

    //Establezca una matriz de campos de encabezado que se enviarán para cada solicitud HTTP
    HTTPCli_setRequestFields(&cli, fields);

    /*!Inicializar la estructura de dirección de socket para el URI dado
    * El formato URI admitido es:
    * - [http [s]: //] nombre_host [: número_puerto] [/ request_uri]
    * Para los casos en los que no se proporciona el puerto, se establece el número de puerto predeterminado.
    */
    ret = HTTPCli_initSockAddr((struct sockaddr *)&addr, HOSTNAME, 0);
    if (ret < 0) {
        printError("httpTask: address resolution failed", ret);
    }

    //Abra una conexión a un servidor HTTP
    ret = HTTPCli_connect(&cli, (struct sockaddr *)&addr, 0, NULL);
    if (ret < 0) {
        printError("httpTask: connect failed", ret);
    }
    System_printf("Request '%s'\n", REQUEST_URI);
    System_flush();

    /*!Realice una solicitud HTTP 1.1 al servidor HTTP
     * Envía una línea de solicitud HTTP 1.1 y los campos
     * de encabezado desde la matriz configurada por el usuario
     * (consulte @ref HTTPCli_setRequestFields ()) al servidor.
     * Además, se pueden enviar al servidor más campos además
     * del conjunto de campos de encabezado establecido por el
     * usuario. Para enviar más campos, configure el `moreFlag`
     * cuando llame a esta función y luego llame a
     * @ref HTTPCli_sendField () con más campos.
     */
    ret = HTTPCli_sendRequest(&cli, HTTPStd_GET, REQUEST_URI, false);
    if (ret < 0) {
        printError("httpTask: send failed", ret);
    }

    //Procesar el encabezado de respuesta del servidor HTTP y devolver el estado
    ret = HTTPCli_getResponseStatus(&cli);
    /*if (ret != HTTPStd_OK) {
        printError("httpTask: cannot get status", ret);
    }*/
    System_printf("HTTP Response Status Code: %d\n", ret);

    /*!Procesar un encabezado de respuesta del servidor HTTP y devolver el campo
     * Filtra los encabezados de respuesta según la matriz de campos
     * (consulte @ref HTTPCli_setResponseFields ()).
     */
    ret = HTTPCli_getResponseField(&cli, data, sizeof(data), &moreFlag);
    if (ret != HTTPCli_FIELD_ID_END) {
        printError("httpTask: response field processing failed", ret);
    }
    len = 0;
    do {
        /*!Leer los datos del cuerpo de la respuesta analizados del servidor HTTP
         *
         * Esta función analiza el cuerpo de la respuesta si el tipo de contenido
         * es codificación de transferencia fragmentada o si el servidor HTTP
         * devuelve el campo de longitud del contenido.
         * Realice una llamada a esta función solo después de la llamada a
         * @refHTTPCli_getResponseStatus () y @refHTTPCli_getResponseField ().
         */
        ret = HTTPCli_readResponseBody(&cli, data, sizeof(data), &moreFlag);
        if (ret < 0) {
            printError("httpTask: response body processing failed", ret);
        }

        len += ret;
    }while (moreFlag);
    System_printf("Body request '%s'\n", data);
    System_flush();

    System_printf("Recieved %d bytes of payload\n", len);
    System_flush();

    //Desconectarse del servidor HTTP y destruir la instancia del cliente HTTP
    HTTPCli_disconnect(&cli);
    //Destruye la instancia del cliente HTTP
    HTTPCli_destruct(&cli);
}
void httpSalida(char decima, char unidad)
{
    //char id;
    //#define REQUEST_URI       "/conexion_in.php?id=2"
    //iota(valor,id);
    char numeros[] ={'/','c','o','n','e','x','i','o','n','_','o','u','t','.','p','h','p','?','i','d','='};
    numeros[21]=decima;
    numeros[22]=unidad;
    //#define REQUEST_URI       "/conexion_out.php?id=1"
    #define REQUEST_URI       numeros
    #define USER_AGENT        "HTTPCli (ARM; TI-RTOS)"
    const char HOSTNAME[] = "proyectousbbog.000webhostapp.com";
    bool moreFlag = false;
    char data[64];
    int ret;
    int len;
    struct sockaddr_in addr;

    HTTPCli_Struct cli;
    HTTPCli_Field fields[3] = {
        { HTTPStd_FIELD_NAME_HOST, HOSTNAME },
        { HTTPStd_FIELD_NAME_USER_AGENT, USER_AGENT },
        { NULL, NULL }
    };
    System_printf("Sending a HTTP GET request OUT to '%s'\n", HOSTNAME);
    System_flush();

    //Crea un nuevo objeto de instancia en la estructura proporcionada
    HTTPCli_construct(&cli);

    //Establezca una matriz de campos de encabezado que se enviarán para cada solicitud HTTP
    HTTPCli_setRequestFields(&cli, fields);

    /*!Inicializar la estructura de dirección de socket para el URI dado
    * El formato URI admitido es:
    * - [http [s]: //] nombre_host [: número_puerto] [/ request_uri]
    * Para los casos en los que no se proporciona el puerto, se establece el número de puerto predeterminado.
    */
    ret = HTTPCli_initSockAddr((struct sockaddr *)&addr, HOSTNAME, 0);
    if (ret < 0) {
        printError("httpTask: address resolution failed", ret);
    }

    //Abra una conexión a un servidor HTTP
    ret = HTTPCli_connect(&cli, (struct sockaddr *)&addr, 0, NULL);
    if (ret < 0) {
        printError("httpTask: connect failed", ret);
    }
    System_printf("Request '%s'\n", REQUEST_URI);
    System_flush();

    /*!Realice una solicitud HTTP 1.1 al servidor HTTP
     * Envía una línea de solicitud HTTP 1.1 y los campos
     * de encabezado desde la matriz configurada por el usuario
     * (consulte @ref HTTPCli_setRequestFields ()) al servidor.
     * Además, se pueden enviar al servidor más campos además
     * del conjunto de campos de encabezado establecido por el
     * usuario. Para enviar más campos, configure el `moreFlag`
     * cuando llame a esta función y luego llame a
     * @ref HTTPCli_sendField () con más campos.
     */
    ret = HTTPCli_sendRequest(&cli, HTTPStd_GET, REQUEST_URI, false);
    if (ret < 0) {
        printError("httpTask: send failed", ret);
    }

    //Procesar el encabezado de respuesta del servidor HTTP y devolver el estado
    ret = HTTPCli_getResponseStatus(&cli);
    /*if (ret != HTTPStd_OK) {
        printError("httpTask: cannot get status", ret);
    }*/
    System_printf("HTTP Response Status Code: %d\n", ret);

    /*!Procesar un encabezado de respuesta del servidor HTTP y devolver el campo
     * Filtra los encabezados de respuesta según la matriz de campos
     * (consulte @ref HTTPCli_setResponseFields ()).
     */
    ret = HTTPCli_getResponseField(&cli, data, sizeof(data), &moreFlag);
    if (ret != HTTPCli_FIELD_ID_END) {
        printError("httpTask: response field processing failed", ret);
    }
    len = 0;
    do {
        /*!Leer los datos del cuerpo de la respuesta analizados del servidor HTTP
         *
         * Esta función analiza el cuerpo de la respuesta si el tipo de contenido
         * es codificación de transferencia fragmentada o si el servidor HTTP
         * devuelve el campo de longitud del contenido.
         * Realice una llamada a esta función solo después de la llamada a
         * @refHTTPCli_getResponseStatus () y @refHTTPCli_getResponseField ().
         */
        ret = HTTPCli_readResponseBody(&cli, data, sizeof(data), &moreFlag);
        if (ret < 0) {
            printError("httpTask: response body processing failed", ret);
        }

        len += ret;
    }while (moreFlag);
    System_printf("Body request '%s'\n", data);
    System_flush();

    System_printf("Recieved %d bytes of payload\n", len);
    System_flush();

    //Desconectarse del servidor HTTP y destruir la instancia del cliente HTTP
    HTTPCli_disconnect(&cli);
    //Destruye la instancia del cliente HTTP
    HTTPCli_destruct(&cli);
}

/*
 *  ======== httpTask ========
 */
Void httpTask(UArg arg0, UArg arg1)
{
    void *netIF;

    /* Open WiFi and await a connection */
    netIF = socketsStartUp();
    char dec='1';
    char uni='0';
    httpSalida(dec,uni);
    /* Close the network - don't do this if other tasks are using it */
    socketsShutDown(netIF);
}

/*
 *  ======== main ========
 */
int main(void)
    {
    Task_Params taskParams;

    /* Call board init functions */
    Board_initGeneral();
    Board_initGPIO();
    Board_initWiFi();

    /* Construct http Task thread */
    Task_Params_init(&taskParams);
    taskParams.stackSize = HTTPTASKSTACKSIZE;
    taskParams.stack = &task0Stack;
    taskParams.priority = 1;
    Task_construct(&task0Struct, (Task_FuncPtr)httpTask, &taskParams, NULL);

    /* Install Button callback */
    GPIO_setCallback(Board_BUTTON0, gpioButtonFxn);

    /* Enable interrupts */
    GPIO_enableInt(Board_BUTTON0);

    /* Turn on user LED */
    GPIO_write(Board_LED0, Board_LED_ON);

    System_printf("Proyecto Request HTTP - NFC/RFID.\n");
    /* SysMin will only print to the console when you call flush or exit */
    System_flush();

    /* Start BIOS */
    BIOS_start();

    return (0);
}
