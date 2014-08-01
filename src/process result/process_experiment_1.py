import numpy as np
import matplotlib.pyplot as plt


if __name__ == '__main__':
	file_object = open('experiment_1')
	try:
		raw_data = file_object.readlines()
	finally:
		file_object.close()

	acc_dict = {}
	miss_recall = []
	err_recall = []
	data_detail = []
	t_len = []
	s_len = []

	count = 0
	tot = 0.0

	for record in raw_data:
		count = count + 1
		data_detail = record[:-1].rsplit(' ')
		tot = tot + float(data_detail[2])
		err_recall.append(float(data_detail[3]))
		miss_recall.append(float(data_detail[4]))
		s_len.append(int(data_detail[0]))
		t_len.append(int(data_detail[1]))
		if count == 10:
			if not acc_dict.has_key(data_detail[1]):
				acc_dict[data_detail[1]] = {}

			acc_dict[data_detail[1]][data_detail[0]] = tot / 10.0
			tot = 0.0
			count = 0

	labels = ['5000', '6000', '7000', '8000', '9000', '10000']

	colors = {
		'50':  'r',
		'100': 'm',
		'150': 'k',
		'200': 'y'
	}

	font = {'family' : 'serif',
        'color'  : 'k',
        'weight' : 'normal',
        'size'   : 16,
        }

	x = [1, 2, 3, 4, 5, 6]

	keys = ['50', '100', '150', '200']

	fig, ax0 = plt.subplots(nrows=1)

	for key in keys:
		y = []
		for label in labels:
			y.append(acc_dict[key][label])
		ax0.plot(x, y, colors[key]+'o')
		ax0.plot(x, y, colors[key], label=key)


	ax0.set_title('Precision corresponding to length', fontdict=font)
	# Now add the legend with some customizations.
	legend = ax0.legend(loc='best', shadow=True)

	# The frame is matplotlib.patches.Rectangle instance surrounding the legend.
	frame  = legend.get_frame()
	frame.set_facecolor('0.90')

	# Set the fontsize
	for label in legend.get_texts():
	    label.set_fontsize('small')

	for label in legend.get_lines():
	    label.set_linewidth(1.5)  # the legend line width
	plt.xticks(x, labels)
	ax0.margins(0.2)

	plt.subplots_adjust(bottom=0.15)
	plt.show()

	fig, ax1 = plt.subplots(nrows=1)

	N = len(miss_recall)
	r = []
	for recall in miss_recall:
		r.append(2 * np.pi * recall)

	r = np.array(r)
	theta = 2 * np.pi * np.random.rand(N)
	area = 100 * r**2 * np.random.rand(N)
	colors = theta

	ax1 = plt.subplot(111, polar=True)
	c = plt.scatter(theta, r, c=colors, s=area, cmap=plt.cm.hsv)
	c.set_alpha(0.75)

	ax1.set_title('Recall rate corresponding to length', fontdict=font)

	plt.subplots_adjust(bottom=0.15)
	plt.show()

	theta = np.linspace(0.0, 2 * np.pi, N, endpoint=False)
	width = np.pi * (np.random.rand(N) * 0.05 + 0.02)
	radii = r;


	ax2 = plt.subplot(111, polar=True)
	bars = ax2.bar(theta, radii, width=width, bottom=0.0)

	for s, bar in zip(s_len, bars):
	    bar.set_facecolor(plt.cm.jet(float(s) / 10000.))
	    bar.set_alpha(0.5)


	ax2.set_title('Recall rate distribution', fontdict=font)
	plt.show()