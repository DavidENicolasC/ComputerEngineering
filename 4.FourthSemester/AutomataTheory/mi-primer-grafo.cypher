//Se crean los nodos
CREATE (Auronplay:canal {name: "AuronPlay"})
CREATE (elrubiusOMG:canal { name:"elrubiusOMG" })
CREATE (julioprofe:canal {name: "julioprofe" })
CREATE (FormulaNoticias:canal {name: "Formula Noticias"})
CREATE (MilenioNoticias:canal {name: "Milenio Noticias"})

//Se crean las relaciones entre los nodos
CREATE (Auronplay)-[:OCHENTA]->(elrubiusOMG)
CREATE (Auronplay)-[:VEINTICINCO]->(FormulaNoticias)
CREATE (FormulaNoticias)-[:OCHENTA]->(MilenioNoticias)
CREATE (FormulaNoticias)-[:VEINTE]->(julioprofe)