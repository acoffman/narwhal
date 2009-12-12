class DashboardController < ApplicationController

  use_google_charts

def index
	overview
end

def overview
  @nav_over = "current"
  dataset1 = GoogleChartDataset.new :data => [10, 20, 30, 40, 50]
  dataset2 = GoogleChartDataset.new :data => [10,50,4,10,16], :color => 'FF0000', :title => 'Traffic'
  data = GoogleChartData.new :datasets => [dataset1, dataset2]
  axis = GoogleChartAxis.new :axis  => [GoogleChartAxis::LEFT, GoogleChartAxis::BOTTOM]
  @chart = GoogleLineChart.new :chart_type => GoogleLineChart::XY , :width => 500, :height => 300, :title => ['Incoming Traffic Rate', 'Configured Allowable Peak and Average Rates']
  @chart.data = data
  @chart.axis = axis
  render :overview
end

def ip
  @nav_ip = "current"
  render :ip
end

def protocols
  @nav_proto = "current"
  render :protocols
end

def rate
  @nav_rate = "current"
  render :rate
end

end
