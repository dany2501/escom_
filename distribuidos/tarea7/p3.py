from pysnmp.hlapi import *

# Definir los parámetros de autenticación SNMPv3
username = 'userAsr'
password = 'pswAsr'
auth_protocol = usmHMACSHAAuthProtocol  # Protocolo de autenticación (usmHMACMD5AuthProtocol o usmHMACSHAAuthProtocol)
privacy_protocol = usmAesCfb128Protocol  # Protocolo de privacidad (usmDESPrivProtocol o usmAesCfb128Protocol)
auth_key = 'claveASR'  # Clave de autenticación (contraseña o frase)
privacy_key = 'claveASRPrivate'  # Clave de privacidad (contraseña o frase)

# Definir la dirección IP de cada router y el OID correspondiente a la memoria libre
routers = [
    {
        'ip': '1.94.100.10',
        'oid': ObjectIdentity('UCD-SNMP-MIB', 'memAvailReal', 0)
    },
    {
        'ip': '1.94.100.11',
        'oid': ObjectIdentity('UCD-SNMP-MIB', 'memAvailReal', 0)
    },
    # Agregar más routers según sea necesario
]

# Recorrer cada router y obtener la memoria libre
for router in routers:
    try:
        error_indication, error_status, error_index, var_binds = next(
            getCmd(SnmpEngine(),
                   UsmUserData(username, auth_key, privacy_key,
                               authProtocol=auth_protocol,
                               privProtocol=privacy_protocol),
                   UdpTransportTarget((router['ip'], 161)),
                   ContextData(),
                   ObjectType(router['oid']))
        )

        if error_indication:
            print(f"Error en {router['ip']}: {error_indication}")
        elif error_status:
            print(f"Error en {router['ip']}: {error_status.prettyPrint()}")
        else:
            for var_bind in var_binds:
                oid, value = var_bind
                memory = int(value)  # Obtener la memoria libre en bytes
                print(f"Memoria libre en {router['ip']}: {memory} bytes")
    except Exception as e:
        print(f"Error en {router['ip']}: {str(e)}")
