// WebPage is stored in the Store data in flash (program) memory instead of SRAM
const char indexPage[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta name="viewport" content="width=device-width, initial-scale = 1">
    <meta charset='UTF-8'>
    <title>IoT dashboard</title>
    <style>
        body {
            font-family: sans-serif;
        }

        .title {
            text-align: center;
            font-size: 250%;
            padding-top: 4vw;
            padding-bottom: 1vw;
            color: #009e84;
        }

        .box {
            display: block;
            border: 1px solid #000;
            border-radius: 50px;
            margin: 0 33%;
        }

        div {
            text-align: center;
            font-size: 130%;
            padding: 20px;
        }

        .button {
            margin: 0 auto;
            padding: 50px;
        }

        #buttonval {
            font-size: 2rem;
            padding: 15px 3%;
        }


        .switch {
            position: relative;
            display: inline-block;
            width: 60px;
            height: 34px;
        }

        /* Hide default HTML checkbox */
        .switch input {
            opacity: 0;
            width: 0;
            height: 0;
        }

        /* The slider */
        .slider {
            position: absolute;
            cursor: pointer;
            top: 0;
            left: 0;
            right: 0;
            bottom: 0;
            background-color: #ccc;
            -webkit-transition: .2s;
            transition: .2s;
            padding: 15px 3%;
        }

        .slider:before {
            position: absolute;
            content: "";
            height: 26px;
            width: 26px;
            left: 4px;
            bottom: 4px;
            background-color: white;
            -webkit-transition: .4s;
            transition: .4s;
        }

        input:checked+.slider {
            background-color: #2196F3;
        }

        input:focus+.slider {
            box-shadow: 0 0 1px #2196F3;
        }

        input:checked+.slider:before {
            -webkit-transform: translateX(26px);
            -ms-transform: translateX(26px);
            transform: translateX(26px);
        }

        /* Rounded sliders */
        .slider.round {
            border-radius: 34px;
        }

        .slider.round:before {
            border-radius: 50%;
        }

        @media only screen and (max-width: 845px) {
            .box {
                display: block;
                border: 1px solid #000;
                border-radius: 50px;
                margin: 0 25%;
            }
        }
    </style>
</head>

<body>
    <h2 class="title">IoT simple dashboard</h2>
    <div class="box">
        <div>Toggle</div>
        <div class="button">
            <label class="switch">
                <input type="checkbox" id="button">
                <span class="slider round"></span>
            </label>
            <div id='buttonval'></div>
        </div>

        <div>Slider</div>
        <input type="range" id="valueslider" name="valueslider" min="0" max="1023">
        <div id='sliderval'></div>
    </div>

    <script>
        // The input objects
        var slider = document.getElementById("valueslider");
        var button = document.getElementById("button");

        //  Objects to display the value
        var outputSlider = document.getElementById("sliderval");
        var outputSwitch = document.getElementById("buttonval");

        //  When the HTML body loads for the first time
        document.body.onload = ()=>{
            outputSlider.innerHTML = slider.value; // Display the default slider value
            outputSwitch.innerHTML = button.checked ? "on" : "off"; // Display the default button value
            xhttp.open("GET", `/switch/?data=${button.checked}`, true);
            xhttp.open("GET", `/switch/?slider=${slider.value}`, true);
            xhttp.send();
        }

        // Update the current button value (each time you toggle the switch)
        button.oninput = () => {
            outputSwitch.innerHTML = button.checked ? "on" : "off";
        }
        
        // Update the current slider value (each time you drag the slider handle)
        slider.oninput = () => {
            outputSlider.innerHTML = slider.value;
        }

        var xhttp = new XMLHttpRequest();
        button.onchange = ()=> {
          xhttp.open("GET", `/switch/?data=${button.checked}`, true);
          xhttp.send();
        }
        slider.onchange = () => {
          xhttp.open("GET", `/switch/?slider=${slider.value}`, true);
          xhttp.send();
        }
    </script>
</body>
</html>
)rawliteral";
