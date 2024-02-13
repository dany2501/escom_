
data = ['BIENES_TRANSP','DESCRIPCION','CANTIDAD','CLAVE_UNIDAD','UNIDAD','MATERIAL_PELIGROSO','PESO_KG','FRACC_ARANC','UUID']
indexes = []

with open('datos.txt', encoding='utf-8-sig') as tlf:
    all_data = [line.strip() for line in tlf.readlines()]
    height_line = all_data[0]
    headers = height_line.split('|')

    for index,header in enumerate(headers):
        try:
            toAppend = data.index(str(header))
            indexes.append(index-1)
            print(header)
        except (ValueError) as ex:
            e = ex

    for i,d in enumerate(all_data):
        if i !=0:
            item = d.split('|')
            item.remove('')
            
            for l,index in enumerate(indexes):
                print(data[l]+": ",item[index])
            print("")