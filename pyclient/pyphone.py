import gobject
import dbus
from dbus.mainloop.glib import DBusGMainLoop


def handle_notification(*args, **kwargs):
    print 'Notification:', args, kwargs


if __name__ == '__main__':


    dbml = DBusGMainLoop(set_as_default=True)

    bus = dbus.SessionBus()
    proxy = bus.get_object('test.signal.source',
        '/test/signal/Object')

    proxy.connect_to_signal('Test', handle_notification)
    loop = gobject.MainLoop()

    dbus.set_default_main_loop(dbml)

    loop.run()