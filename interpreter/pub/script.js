let data = {};

let xhr = new XMLHttpRequest();
xhr.open("GET", "./all.json");
xhr.addEventListener("readystatechange", e => {
    if(xhr.readyState != 4) return;
    if(xhr.status != 200) return console.error(`Bad xhr http code ${xhr.status}`);

    data = JSON.parse(xhr.responseText);
    doGraph();
});
xhr.send();

function reformat(data) {
    let result = {};
    result.x = [];
    for(let i in data) {
        let piece = data[i];
        if(!piece["accel_x"]) continue;
        result.x.push(i);

        for(let i in piece) {
            if(i == "accel_calib" || i == "rot_calib") continue;
            if(!result[i]) result[i] = [];
            result[i].push(piece[i]);
        }
    }

    return result;
}

function doGraph() {
    console.log(data);
    let real = reformat(data);

    new Chart("chart", {
        type: "line",
        data: {
            labels: real.x,
            datasets: [
                {
                    data: real["accel_x"],
                    borderColor: "red",
                    fill: false,
                    label: "Accel X"
                },
                {
                    data: real["accel_y"],
                    borderColor: "green",
                    fill: false,
                    label: "Accel Y"
                },
                {
                    data: real["accel_z"],
                    borderColor: "blue",
                    fill: false,
                    label: "Accel Z"
                },

                {
                    data: real["rot_x"],
                    borderColor: "cyan",
                    fill: false,
                    label: "Rotation X"
                },
                {
                    data: real["rot_y"],
                    borderColor: "magenta",
                    fill: false,
                    label: "Rotation Y"
                },
                {
                    data: real["rot_z"],
                    borderColor: "yellow",
                    fill: false,
                    label: "Rotation Z"
                }
            ]
        },
        options: {
            legend: {display: false}
        }
    });
}