# Protocol

The [IRMP library](https://github.com/ukw100/IRMP) gives us an ```Address``` and a ```Command``` which, in total, give us 24 bits. Turns out the IR protocol for the SAC12010QC is as simple as they get. No CRC's, no hashes, nothing. Raw bits. Below tables explain how the ```Address``` (2 bytes, 16 bits) and ```Command``` (1 byte, 8 bits) make up the entire protocol.

<table>
  <tr><th colspan="2" align="left"><h2>Address</h2></th></tr>
  <tr valign="top">
    <td>
      <table>
        <tr>
          <th>Bit</th>
          <th><code>5432109876543210</code></th>
        </tr>
        <tr>
          <td>Function</td>
          <td><code>HGGFEEEE0DCCBAAA</code></td>
        </tr>
      </table>
    </td>
    <td>
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
          <td>0</td>
          <td>7</td>
          <td>Zero</td>
          <td>Always <code>0</code></td>
        </tr>
        <tr valign="top">
          <td>E</td>
          <td>8 to 11</td>
          <td>Temperature</td>
          <td>Offset from 16°C, ranging from 16°C (<code>0000</code>) to 30°C (<code>1110</code>)</td>
        </tr>
        <tr valign="top">
          <td>F, G, H</td>
          <td>12 to 15</td>
          <td>Timer</td>
          <td>See <a href="#timer">Timer</a></td>
        </tr>
      </table>
    </td>
  </tr>
  <tr><th colspan="2" align="left"><h2>Command</h2></th></tr>
  <tr valign="top">
    <td>
      <table>
        <tr>
          <th>Bit</th>
          <th><code>76543210</code></th>
        </tr>
        <tr>
          <td>Function</td>
          <td><code>VWXYZZZZ</code></td>
        </tr>
      </table>
    </td>
    <td>
      <table>
        <tr>
          <th>Function</th>
          <th>Bits</th>
          <th>Description</th>
          <th>Values</th>
        </tr>
        <tr valign="top">
          <td>Z</td>
          <td>0 to 3</td>
          <td>Timer</td>
          <td>See <a href="#timer">Timer</a></td>
        </tr>
        <tr valign="top">
          <td>Y</td>
          <td>4</td>
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
          <td>X</td>
          <td>5</td>
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
          <td>W</td>
          <td>6</td>
          <td>Christmastree</td>
          <td>
            No clue what this does, but it shows a 🎄 on the LCD display on the remote.
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
          <td>V</td>
          <td>7</td>
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
      </table>
    </td>
  </tr>
</table>

## Timer
The timer on/off state is indicated by address bit `15` (`H`, or the address' MSB). Bit `12` (`F`) is the half hour indicator. Bits `13` and `14` (`G`) of the address are the tens position of the 24 hour clock and bits `0` to `3` of the command (`Z`) are the ones position of the 24 hour clock (essentially [BCD encoding](https://en.wikipedia.org/wiki/Binary-coded_decimal) the time). The time is calculated by composing the `GGZZZZF` bits where `G` is the 'tens' part, `Z` is the 'ones' part and `F` is the half-hour indicator (`0` being 0, `1` being ½ an hour).

Let's take the following example:

            Address          Command
            1011010001001001 00000111
    Meaning HGGFEEEE0DCCBAAA VWXYZZZZ

Let's mask out the bits we're not interested in:

            Address          Command
            1011............ ....0111
    Meaning HGGF............ ....ZZZZ

This gives us:

    H GG ZZZZ F
    1 01 0111 1
    | |/ \  / |
    | |   \/  |
    | 1   7   ½
    |
    Timer on (1)

Or: 17.5 hours.