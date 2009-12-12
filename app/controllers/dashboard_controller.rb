class DashboardController < ApplicationController

  use_google_charts

def index
	overview
end

def edit_num
  @test_num = params[:value]
  render :text => @test_num
end

def overview
  @test_num = params[:test_num]
  @test_num ||= 5
  @nav_over = "current"
  dataset3 = GoogleChartDataset.new :data => [0,100]
  dataset4 = GoogleChartDataset.new :data => [@test_num, @test_num], :color => 'FF0000', :title => 'Allowable Rate'
  dataset1 = GoogleChartDataset.new :data => [10, 20, 30, 40, 50]
  dataset2 = GoogleChartDataset.new :data => [10,50,4,10,16], :color => 'FF0000', :title => 'Traffic'
  data = GoogleChartData.new :datasets => [dataset1, dataset2, dataset3, dataset4]
  axis = GoogleChartAxis.new :axis  => [GoogleChartAxis::LEFT, GoogleChartAxis::BOTTOM]
  @chart = GoogleLineChart.new :chart_type => GoogleLineChart::XY , :width => 500, :height => 300, :title => ['Incoming Traffic Rate', 'Configured Allowable Peak and Average Rates']
  @chart.data = data
  @chart.axis = axis
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
