version = 3
from pysnmp.hlapi import *
def despliega(iterador):
    while True:
        try:
            errorIndication, errorStatus, errorIndex, varBinds = next(iterador)
            if not errorIndication and not errorStatus:
                for varBind in varBinds:
                    print(varBind)
            else:
                print("Error:",errorStatus)
        except StopIteration:
            return

def set_descripcion(router):
    ip = '1.9.200.10'
    puerto = 161
    OID = '1.3.6.1.2.1.31.1.1.1.18.' + str(router + 2) # descripcion
    valor = "Gi" + str(router) + "/0"
    cadena_comunidad = 'prueba'

    switcher = {
        2: CommunityData(cadena_comunidad, mpModel=1),
        3: UsmUserData('usuario',authKey='password123',authProtocol=usmHMACSHAAuthProtocol,privKey='password123',privProtocol=usmAesCfb128Protocol)
    }

    iterador = setCmd(
        SnmpEngine(),
        switcher.get(version),
        UdpTransportTarget((ip,puerto)),
        ContextData(),
        ObjectType(ObjectIdentity(OID),valor))
    despliega(iterador)

for i in range(0,7):
    set_descripcion(i)
