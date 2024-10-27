# Protocol

The SAC9010QC/SAC12010QC uses a 36 bit code. Below you'll find a specification of what each of the bits do. The bits marked `X` are constant as far as I could figure out.

<table>
  <tr valign="top">
    <th>Bit</th>
    <th>
      <code>333333222222222211111111110000000000</code><br>
      <code>543210987654321098765432109876543210</code>
    </th>
  </tr>
  <tr>
    <td>Function</td>
    <td><code>XXXXXXXXXXQQPNMLKKKKJHHGFFFFEDCCBAAA</code></td>
  </tr>
</table>

## Functions

<table>
  <tr>
    <th>Function</th>
    <th>Bits</th>
    <th>Description</th>
    <th>Values</th>
  </tr>
  <tr valign="top">
    <td>A</td>
    <td>0, 1 and 2</td>
    <td>Mode</td>
    <td>
      <table>
        <tr>
          <th>Value</th>
          <th>Description</th>
        </tr>
        <tr>
          <td><code>000</code></td>
          <td>Auto</td>
        </tr>
        <tr>
          <td><code>001</code></td>
          <td>Cool</td>
        </tr>
        <tr>
          <td><code>010</code></td>
          <td>Dehumidify</td>
        </tr>
        <tr>
          <td><code>011</code></td>
          <td>Fan</td>
        </tr>
        <tr>
          <td><code>100</code></td>
          <td>Heat</td>
        </tr>
      </table>
    </td>
  </tr>
  <tr valign="top">
    <td>B</td>
    <td>3</td>
    <td>Power</td>
    <td>
      <table>
        <tr>
          <th>Value</th>
          <th>Description</th>
        </tr>
        <tr>
          <td><code>0</code></td>
          <td>Off</td>
        </tr>
        <tr>
          <td><code>1</code></td>
          <td>On</td>
        </tr>
      </table>
    </td>
  </tr>
  <tr valign="top">
    <td>C</td>
    <td>4, 5</td>
    <td>Fan speed</td>
    <td>
      <table>
        <tr>
          <th>Value</th>
          <th>Description</th>
        </tr>
        <tr>
          <td><code>00</code></td>
          <td>Auto</td>
        </tr>
        <tr>
          <td><code>01</code></td>
          <td>1</td>
        </tr>
        <tr>
          <td><code>10</code></td>
          <td>2</td>
        </tr>
        <tr>
          <td><code>11</code></td>
          <td>3</td>
        </tr>
      </table>
    </td>
  </tr>
  <tr valign="top">
    <td>D</td>
    <td>6</td>
    <td>Swing</td>
    <td>
      <table>
        <tr>
          <th>Value</th>
          <th>Description</th>
        </tr>
        <tr>
          <td><code>0</code></td>
          <td>Off</td>
        </tr>
        <tr>
          <td><code>1</code></td>
          <td>On</td>
        </tr>
      </table>
    </td>
  </tr>
  <tr valign="top">
    <td>E</td>
    <td>7</td>
    <td>Sleep</td>
    <td>
      <table>
        <tr>
          <th>Value</th>
          <th>Description</th>
        </tr>
        <tr>
          <td><code>0</code></td>
          <td>Off</td>
        </tr>
        <tr>
          <td><code>1</code></td>
          <td>On</td>
        </tr>
      </table>
    </td>
  </tr>
  <tr valign="top">
    <td>F</td>
    <td>8 to 11</td>
    <td>Temperature</td>
    <td>Offset from 16°C, ranging from<br>16°C (<code>0000</code>) to 30°C (<code>1110</code>)</td>
  </tr>
  <tr valign="top">
    <td>G, H, J, K</td>
    <td>12 to 19</td>
    <td>Timer</td>
    <td>See <a href="#timer">Timer</a></td>
  </tr>
  <tr valign="top">
    <td>L</td>
    <td>20</td>
    <td>Humid</td>
    <td>
      <table>
        <tr>
          <th>Value</th>
          <th>Description</th>
        </tr>
        <tr>
          <td><code>0</code></td>
          <td>Off</td>
        </tr>
        <tr>
          <td><code>1</code></td>
          <td>On</td>
        </tr>
      </table>
    </td>
  </tr>
  <tr valign="top">
    <td>M</td>
    <td>21</td>
    <td>Light</td>
    <td>
      <table>
        <tr>
          <th>Value</th>
          <th>Description</th>
        </tr>
        <tr>
          <td><code>0</code></td>
          <td>Off</td>
        </tr>
        <tr>
          <td><code>1</code></td>
          <td>On</td>
        </tr>
      </table>
    </td>
  </tr>
  <tr valign="top">
    <td>N</td>
    <td>22</td>
    <td>Air ionizer</td>
    <td>
      <table>
        <tr>
          <th>Value</th>
          <th>Description</th>
        </tr>
        <tr>
          <td><code>0</code></td>
          <td>Off</td>
        </tr>
        <tr>
          <td><code>1</code></td>
          <td>On</td>
        </tr>
      </table>
    </td>
  </tr>
  <tr valign="top">
    <td>P</td>
    <td>23</td>
    <td>Save</td>
    <td>
      <table>
        <tr>
          <th>Value</th>
          <th>Description</th>
        </tr>
        <tr>
          <td><code>0</code></td>
          <td>Off</td>
        </tr>
        <tr>
          <td><code>1</code></td>
          <td>On</td>
        </tr>
      </table>
    </td>
  </tr>
  <tr valign="top">
    <td>Q</td>
    <td>24, 25</td>
    <td>Air</td>
    <td>
      <table>
        <tr>
          <th>Value</th>
          <th>Description</th>
        </tr>
        <tr>
          <td><code>00</code></td>
          <td>-</td>
        </tr>
        <tr>
          <td><code>01</code></td>
          <td>Air 1</td>
        </tr>
        <tr>
          <td><code>10</code></td>
          <td>Air 2</td>
        </tr>
      </table>
    </td>
  </tr>
</table>

## Timer
The timer on/off state is indicated by address bit `15` (`J`). Bit `12` (`G`) is the half hour indicator. Bits `13` and `14` (`H`) of the address are the tens position of the 24 hour clock and bits `16` to `19` of the command (`K`) are the ones position of the 24 hour clock (essentially [BCD encoding](https://en.wikipedia.org/wiki/Binary-coded_decimal) the time). The time is calculated by composing the `HHKKKKG` bits where `H` is the 'tens' part, `K` is the 'ones' part and `G` is the half-hour indicator (`0` being 0, `1` being ½ an hour).

Let's take the following example:

            000000000000000001111011010001001001 
    Meaning XXXXXXXXXXQQPNMLKKKKJHHGFFFFEDCCBAAA

Let's mask out the bits we're not interested in:

            ................01111011............ 
    Meaning ................KKKKJHHG............ 

This gives us:

    J HH KKKK G
    1 01 0111 1
    | |/ \  / |
    | |   \/  |
    | 1   7   ½
    |
    Timer on (1)

Or: 17.5 hours.
