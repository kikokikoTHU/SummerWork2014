import numpy as np
import matplotlib.pyplot as plt


if __name__ == '__main__':
	file_object = open('experiment_2')
	try:
		raw_data = file_object.readlines()
	finally:
		file_object.close()

	acc_dict = {}
	miss_recall = []
	err_recall = []
	data_detail = []

	count = 0
	tot = 0.0

	for record in raw_data:
		count = count + 1
		data_detail = record[:-1].rsplit(' ')
		tot = tot + float(data_detail[2])
		err_recall.append(float(data_detail[3]))
		miss_recall.append(float(data_detail[4]))
		if count == 10:
			if not acc_dict.has_key(data_detail[1]):
				acc_dict[data_detail[1]] = {}

			acc_dict[data_detail[1]][data_detail[0]] = tot / 10.0
			tot = 0.0
			count = 0

	labels = ['0.002', '0.004', '0.006', '0.008', '0.01']

	colors = {
		'0.002': 'r',
		'0.004': 'm',
		'0.006': 'k',
		'0.008': 'y',
		'0.01':  'g' 
	}

	font = {'family' : 'serif',
        'color'  : 'k',
        'weight' : 'normal',
        'size'   : 16,
        }

	x = [1, 2, 3, 4, 5]

	keys = ['0.002', '0.004', '0.006', '0.008', '0.01']

	fig, ax0 = plt.subplots(nrows=1)

	for key in keys:
		y = []
		for label in labels:
			y.append(acc_dict[key][label])
		ax0.plot(x, y, colors[key]+'o')
		ax0.plot(x, y, colors[key], label=key)


	ax0.set_title('Precision corresponding to p and q', fontdict=font)
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
	
	ax1.set_title('Recall rate corresponding to p and q', fontdict=font)

	plt.subplots_adjust(bottom=0.15)
	plt.show()