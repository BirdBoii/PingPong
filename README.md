# PingPong
A simple Arduino based ping pong project I had made to challenge myself as one of my first complete, self made hardware based projects. 

<h3>Challanges</h3>
In this project, one of the major challanges that I had was the fact that the arduino Uno had less keys than what I had needed to power both the 8x8 LED matrix as well as the 4 buttons (2 for each player). To overcome this challange, I connected the resistors and switches in such a way that engaging a switch would add in a resistor in series/parallel, thus varying the value of the analog input. The analog input was segrigrated into different ranges, and accordingly, each range corrosponded to a different combinations of buttons being pressed. Thus using a single analog input pin, we can somewhat accurately determine the state of 4 buttons.<br>

Another challange, was due to the fact that I did not have a sufficient amount of the same resistors, meaning some lines appeared darker than others. In the end, this could be solved by setting some pwm values to lower the brightness of the other lights, or even get more resistors. Howeaver, I choose to ignore it as it did not have much of an effect on the functionality of the game.
