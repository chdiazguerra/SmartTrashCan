var mymap;

var verde = L.icon({
    iconUrl: 'media/verde.svg',
    iconSize:     [30, 30], // size of the icon
    iconAnchor:   [15, 30], // point of the icon which will correspond to marker's location
    popupAnchor:  [0, -30] // point from which the popup should open relative to the iconAnchor
});

var amarillo= L.icon({
    iconUrl: 'media/amarillo.svg',
    iconSize:     [30, 30], // size of the icon
    iconAnchor:   [15, 30], // point of the icon which will correspond to marker's location
    popupAnchor:  [0, -30] // point from which the popup should open relative to the iconAnchor
});

var rojo = L.icon({
    iconUrl: 'media/rojo.svg',
    iconSize:     [30, 30], // size of the icon
    iconAnchor:   [15, 30], // point of the icon which will correspond to marker's location
    popupAnchor:  [0, -30] // point from which the popup should open relative to the iconAnchor
});

var desconectado = L.icon({
    iconUrl: 'media/desconectado.svg',
    iconSize:     [30, 30], // size of the icon
    iconAnchor:   [15, 30], // point of the icon which will correspond to marker's location
    popupAnchor:  [0, -30] // point from which the popup should open relative to the iconAnchor
});

var states = {};
states[0] = desconectado;
states[1] = verde;
states[2] = amarillo;
states[3] = rojo;

var basureros = {};

function loadMap(){
    mymap = L.map('map').setView([-33.45780, -70.66239], 19);
    L.tileLayer('https://api.mapbox.com/styles/v1/{id}/tiles/{z}/{x}/{y}?access_token={accessToken}', {
        attribution: 'Map data &copy; <a href="https://www.openstreetmap.org/copyright">OpenStreetMap</a> contributors, Imagery © <a href="https://www.mapbox.com/">Mapbox</a>',
        maxZoom: 20,
        id: 'mapbox/streets-v11',
        tileSize: 512,
        zoomOffset: -1,
        accessToken: 'YOUR_TOKEN'
    }).addTo(mymap);

    getbasureros();

}

markers = {};

function loadMarkers(){

    for (let basurero in basureros){
        let popup = '<b> Hora: ' + basureros[basurero][4] + '</b>';
        if (basurero in markers){
            markers[basurero].setIcon(states[basureros[basurero][3]]).setPopupContent(popup);
        } else {
            markers[basurero] = L.marker([basureros[basurero][1], basureros[basurero][2]], {icon: states[basureros[basurero][3]]}).addTo(mymap);
            markers[basurero].bindPopup(popup);
        }
    }

}

function getbasureros(){
    const xhttp = new XMLHttpRequest();

    xhttp.onload = function (datos){
        let response = datos.currentTarget.responseText;
        let res = JSON.parse(response);
        res.forEach(function (basurero){
            basureros[basurero['id']] = [basurero['num'], basurero['lat'], basurero['lon'], 0, 0];
        });

        getstates();
    }

    xhttp.open('POST', 'php/getbasureros.php', true);
    xhttp.send();
}

var hora;
function getstates(){
    const xhttp = new XMLHttpRequest();

    xhttp.onload = function (datos){
        let response = datos.currentTarget.responseText;
        let res = JSON.parse(response);
        hora = Date.parse(res[res.length-1]);
        for (let i=0; i<res.length-1; i++){
            basureros[res[i]['id']][4] = res[i]['fecha'];
            fecha_basurero = Date.parse(res[i]['fecha']);
            if ((hora - fecha_basurero > 300000) && (res[i]['id'] == '6f20b65f89d4ccd')){ //Pasaron mas de 5 minutos sin info
                basureros[res[i]['id']][3] = 0;
            } else {
                basureros[res[i]['id']][3] = res[i]['estado'];
            }

            actualizarAlerta(res[i]['id'], basureros[res[i]['id']][3], res[i]['fecha'], basureros[res[i]['id']][0]);
            
        }

        loadMarkers();
        
    }

    xhttp.open('POST', 'php/getstate.php', true);
    xhttp.send();
}

function actualizarAlerta(id, estado, fecha, num){
    let alertdiv = document.getElementById('alertdiv');
    let alertacheck = document.getElementById(id);
    if (estado == 0 && alertacheck == null){
        let alerta = document.createElement('div');
        alerta.setAttribute('class', 'alertdesconectado');
        alerta.setAttribute('id', id);
        alerta.setAttribute('onclick', "zoom(this.id);");
        alerta.innerHTML = '<p> Fecha: ' + fecha + '</p>' +  '<p>Basurero ' + num + ' desconectado</p>';
        alertdiv.appendChild(alerta);
    } else if (estado == 3 && alertacheck == null){
        let alerta = document.createElement('div');
        alerta.setAttribute('class', 'alertlleno');
        alerta.setAttribute('id', id);
        alerta.setAttribute('onclick', "zoom(this.id);");
        alerta.innerHTML = '<p> Fecha: ' + fecha + '</p>' +  '<p>Basurero ' + num + ' lleno</p>';
        alertdiv.appendChild(alerta);
    } else if ((estado == 1 || estado == 2) && alertacheck != null) {
            alertacheck.remove();
    }
}

function zoom(id){
    mymap.setView([basureros[id][1], basureros[id][2]], 20);
}
setInterval(getstates, 10000);