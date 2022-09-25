#define DBUS_API_SUBJECT_TO_CHANGE
#include <dbus/dbus.h>
#include <stdbool.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>


/**
 * Connect to the DBUS bus and send a broadcast signal
 */
void sendsignal(char* sigvalue)
{
   DBusMessage* msg;
   DBusMessageIter args;
   DBusConnection* conn;
   DBusError err;
   int ret;
   dbus_uint32_t serial = 0;

   printf("Sending signal with value %s\n", sigvalue);

   // initialise the error value
   dbus_error_init(&err);

   // connect to the DBUS system bus, and check for errors
   conn = dbus_bus_get(DBUS_BUS_SYSTEM, &err);
   if (dbus_error_is_set(&err)) { 
      fprintf(stderr, "Connection Error (%s)\n", err.message); 
      dbus_error_free(&err); 
   }
   if (NULL == conn) { 
      exit(1); 
   }

   // register our name on the bus, and check for errors
   ret = dbus_bus_request_name(conn, "test.signal.sink", DBUS_NAME_FLAG_ALLOW_REPLACEMENT , &err);
   if (dbus_error_is_set(&err)) { 
      fprintf(stderr, "Name Error (%s)\n", err.message); 
      dbus_error_free(&err); 
   }
   if (DBUS_REQUEST_NAME_REPLY_IN_QUEUE != ret) {
      exit(1);
   }
   while (true) {
      // create a signal & check for errors 
      msg = dbus_message_new_signal("/test/signal/Object", // object name of the signal
				    "test.signal.Type", // interface name of the signal
				    "Test"); // name of the signal
      if (NULL == msg) 
      { 
	  fprintf(stderr, "Message Null\n"); 
	  exit(1); 
      }

      // append arguments onto signal
      dbus_message_iter_init_append(msg, &args);
      if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_STRING, &sigvalue)) {
	  fprintf(stderr, "Out Of Memory!\n"); 
	  exit(1);
      }

      // send the message and flush the connection
      if (!dbus_connection_send(conn, msg, &serial)) {
	  fprintf(stderr, "Out Of Memory!\n"); 
	  exit(1);
      }
      printf("Signal Sent\n");
      sleep(5);
   }
   
   dbus_connection_flush(conn);
   
   //printf("Signal Sent\n");
   
   // free the message and close the connection
   dbus_message_unref(msg);
   //dbus_connection_close(conn);
}

int main(int argc, char** argv)
{
   sendsignal("\nASDFASDFASDFASDFASDFASDFASDFASDFASDFASDFASDF\n");
   return 0;
}