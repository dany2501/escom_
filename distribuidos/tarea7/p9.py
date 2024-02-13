from pysnmp.hlapi import *

# Definir los parámetros de autenticación SNMPv3
username = 'userAsr'
password = 'pswAsr'
auth_protocol = usmHMACSHAAuthProtocol  # Protocolo de autenticación (usmHMACMD5AuthProtocol o usmHMACSHAAuthProtocol)
privacy_protocol = usmAesCfb128Protocol  # Protocolo de privacidad (usmDESPrivProtocol o usmAesCfb128Protocol)
auth_key = 'claveASR'  # Clave de autenticación (contraseña o frase)
privacy_key = 'claveASRPrivate'  # Clave de privacidad (contraseña o frase)

# Definir la dirección IP y la interfaz a encender en cada router
routers = [
    {
        'ip': '1.94.100.10',
        'interface': 'Gi2/0'
    },
    {
        'ip': '1.94.100.11',
        'interface': 'Gi1/0'
    }
]

# Recorrer cada router y encender la interfaz especificada
for router in routers:
    try:
        # Encender la interfaz
        error_indication, error_status, error_index, var_binds = next(
            setCmd(SnmpEngine(),
                   UsmUserData(username, auth_key, privacy_key,
                               authProtocol=auth_protocol,
                               privProtocol=privacy_protocol),
                   UdpTransportTarget((router['ip'], 161)),
                   ContextData(),
                   ObjectType(ObjectIdentity('IF-MIB', 'ifAdminStatus', router['interface'])).set(1)  # 1 es el valor para encender la interfaz
                   )
        )

        if error_indication:
            print(f"Error en {router['ip']}: {error_indication}")
        elif error_status:
            print(f"Error en {router['ip']}: {error_status.prettyPrint()}")
        else:
            print(f"Interfaz {router['interface']} encendida en {router['ip']}")
    except Exception as e:
        print(f"Error en {router['ip']}: {str(e)}")
