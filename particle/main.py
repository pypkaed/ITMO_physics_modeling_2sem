import pandas as pd
import math

L = 32 / 100                # m
dist = (24 - 11.5) / 100    # m
Vstart = 7 * pow(10, 5)     # m/sec
m = 9.1 * pow(10, -31)      # kg
q = -1.6 * pow(10, -19)     # Кл

tmax = L / Vstart
Umin = abs(m * dist ** 2 * Vstart ** 2 / (q * L ** 2))
Vend = math.sqrt(Vstart ** 2 + Vstart ** 2 * dist ** 2 / L ** 2)

koeff = dist / (2 * L ** 2)
xend = Vstart * tmax
accel = dist / tmax ** 2

#                   === excel shit ===

writer = pd.ExcelWriter('charts.xlsx', engine='xlsxwriter')

#                       graph y(t):
df1 = pd.DataFrame({'y': [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
                   't': [0, 0, 0, 0, 0, 0, 0, 0, 0, round(tmax * 10 ** 7, 2)]
                   })
for i in range(1, 9):
    df1.loc[i, 't'] = df1.loc[i - 1, 't'] + 0.45
for i in range(10):
    df1.loc[i, 'y'] = accel * df1.loc[i, 't'] ** 2 / 2

df1.to_excel(writer, sheet_name='Sheet1', index=False)

workbook = writer.book
worksheet = writer.sheets['Sheet1']

chart = workbook.add_chart({'type': 'line'})
chart.add_series({
    'values': '=\'Sheet1\'!$A$2:$A$11',
    'categories': '=\'Sheet1\'!$B$2:$B$11'
})

chart.set_x_axis({'name': 'time, sec * 10^7'})
chart.set_y_axis({'name': 'y, m'})
chart.set_legend({'position': 'none'})

worksheet.insert_chart('D2', chart)

#                       graph y(x):

df2 = pd.DataFrame({'y': [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
                   'x': [0, 0, 0, 0, 0, 0, 0, 0, 0, round(xend, 2)]
                   })
for i in range(1, 9):
    df2.loc[i, 'x'] = df2.loc[i - 1, 'x'] + 0.032
for i in range(10):
    df2.loc[i, 'y'] = koeff * df2.loc[i, 'x'] ** 2

df2.to_excel(writer, sheet_name='Sheet1', startrow=18, index=False)

chart2 = workbook.add_chart({'type': 'line'})
chart2.add_series({
    'values': '=\'Sheet1\'!$A$20:$A$29',
    'categories': '=\'Sheet1\'!$B$20:$B$29'
})

chart2.set_x_axis({'name': 'x, m'})
chart2.set_y_axis({'name': 'y, m'})
chart2.set_legend({'position': 'none'})

worksheet.insert_chart('D20', chart2)

#                       graph ay(t):

df3 = pd.DataFrame({'ay': [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
                    't': [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
                   })
for i in range(10):
    df3.loc[i, 't'] = round(tmax * 10 ** 7, 2)
    df3.loc[i, 'ay'] = dist / df3.loc[i, 't'] ** 2

df3.to_excel(writer, sheet_name='Sheet1', startcol=12, index=False)

chart3 = workbook.add_chart({'type': 'line'})
chart3.add_series({
    'values': '=\'Sheet1\'!$M$2:$M$11',
    'categories': '=\'Sheet1\'!$N$2:$N$11'
})

chart3.set_x_axis({'name': 'time, sec * 10^7'})
chart3.set_y_axis({'name': 'ay, m/sec^2'})
chart3.set_legend({'position': 'none'})

worksheet.insert_chart('P2', chart3)

#                       graph Vy(t):

df4 = pd.DataFrame({'Vy': [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
                    't': [0, 0, 0, 0, 0, 0, 0, 0, 0, round(tmax * 10 ** 7, 2)]
                   })
for i in range(1, 9):
    df4.loc[i, 't'] = df4.loc[i - 1, 't'] + 0.45
for i in range(10):
    df4.loc[i, 'Vy'] = accel * df4.loc[i, 't']

df4.to_excel(writer, sheet_name='Sheet1', startcol=12, startrow=18, index=False)

chart4 = workbook.add_chart({'type': 'line'})
chart4.add_series({
    'values': '=\'Sheet1\'!$M$20:$M$29',
    'categories': '=\'Sheet1\'!$N$20:$N$29'
})

chart4.set_x_axis({'name': 'time, sec * 10^7'})
chart4.set_y_axis({'name': 'Vy, m/sec'})
chart4.set_legend({'position': 'none'})

worksheet.insert_chart('P20', chart4)

writer.save()

#                  === end of excel shit ===

print(tmax)
print(Umin)
print(Vstart)
print(Vend)
