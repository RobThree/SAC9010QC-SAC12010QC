# Protocol

Below tables explain the ```Address``` (2 bytes, 16 bits) and ```Command``` (1 byte, 8 bits)

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
          <td><code>TTTTTTTT0SFFPMMM</code></td>
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
          <td>M</td>
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
          <td>P</td>
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
          <td>F</td>
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
          <td>S</td>
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
          <td>T</td>
          <td>8 to 15</td>
          <td>Temperature</td>
          <td>See <a href="#timer-and-temperature">Timer &amp; Temperature</a></td>
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
          <td><code>SXLHTTTT</code></td>
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
          <td>T</td>
          <td>0 to 3</td>
          <td>Timer</td>
          <td>See <a href="#timer-and-temperature">Timer &amp; Temperature</a></td>
        </tr>
        <tr valign="top">
          <td>H</td>
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
          <td>L</td>
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
          <td>X</td>
          <td>6</td>
          <td>Christmas(?)</td>
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
          <td>S</td>
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

## Timer and Temperature
TODO